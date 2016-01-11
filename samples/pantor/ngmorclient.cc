// Copyright (c), Pantor Engineering AB, 1999-2010
// All rights reserved

///////////////////////////////////////////////////////////////////////////
//
//   This is a sample FIX client that gives an overview of the basic
//   features of the Presto FIX library. The sample shows how to setup
//   an initiator and how to send and receive FIX messages.
//
//   The bulk of the setup is handled in the run () function. The
//   sending is performed by the sampleWorker () function and the
//   handling of received messages is done in the SampleObs struct.
//
///////////////////////////////////////////////////////////////////////////

#include "presto/base/RuntimeEnv.h"
#include "presto/base/DataModel.h"
#include "base/app/CmdLine.h"
#include "presto/fix/IoEventLoopTransport.h"
#include "presto/fix/Session.h"
#include "presto/fix/JournalMessageStore.h"
#include "presto/fix/FastCodec.h"
#include "presto/fix/TvCodec.h"
#include "presto/fix/Initiator.h"
#include "presto/fix/ActivityLogPolicy.h"
#include "base/xymo/Alloc.h"
#include "presto/if/scp/gen/OrgFixprotocolFastScp11TypeInfo.h"
#include "base/app/ParameterSet.h"

#include "presto/if/ngm/gen/Fix50Observer.h"

using namespace Pantor;
using namespace Presto;

namespace Scp = Org::Fixprotocol::Fast::Scp11;

// Command line specification

static const char * FixClientCmdLine =
   "ngmorclient [-h/--help]                     # Display this help"
   "            [-L/--lib <dir-or-jar>...]        # Resource library path"
   "            -a/--address <host:port>...       # Hosts and ports"
   "            -s/--schema <schema-file>...      # FMS Schema"
   "            -T/--templates <template-file>... # FAST templates"
   "            -I/--initiator <sender-comp-id>   # SenderCompID"
   "            [-i/--intorsubid <sender-sub-id>] # SendersubID"
   "            -A/--acceptor <target-comp-id>    # TargetCompID"
   "            -u/--username <username>          # Username"
   "            -p/--password <password>          # Password"
   "            [--tv]                            # Use tag/value encoding"
   "            [-b/--actorsubid <target-sub-id>] # TargetSubID"
   "            [-v/--verbosity <level>]          # Verbosity level"
   "            [-t/--trace...]                   # Trace level"
   "            [-r/--reset-on-logon]             # Reset seqNum to 1 on logon"
   ;


// The sample observer observs execution reports

struct SampleObs : public Fix50::Fix50Observer
{
   SampleObs (const Fix::Initiator & intor_) : intor (intor_) { }

   // onExecutionReport gets called whenever an execution report
   // arrives. In this sample implementation we just dump the ER as
   // text to the standard error stream.
   
   void onExecutionReport (const Fix50::ExecutionReport::Ptr & er)
   {
      intor.getDataModel ().writeAsText (er, std::cerr);
   }

   void onHello (const Scp::Hello::Ptr & msg)
   {
      intor.getDataModel ().writeAsText (msg, std::cerr);
   }
   
   void onAlert (const Scp::Alert::Ptr & msg)
   {
      intor.getDataModel ().writeAsText (msg, std::cerr);
   }
   
   const Fix::Initiator & intor;
};

// The sample worker sends a NewOrderSingle every five seconds if the
// session is on-line

void
sampleWorker (Fix::IoEventLoopTransport::IntervalControl &,
              const Fix::Session::Ptr & s)
{
   if (! s->isLoggedOn () || ! s->isConnected ())
   {
      s->log ("Not logged on or not connected, retrying ...");
      return;
   }
   
   // Create and send a NewOrderSingle

   Xing::ObjHandle<Fix50::NewOrderSingle> nos;
   nos->setClOrdID ("FIXME", nos);
   nos->setOrdType (Fix50::OrdTypeLimit_2);
   nos->setOrderQty (Decimal (100));
   nos->setPrice (Decimal (17));
   nos->setSide (Fix50::SideBuy_1);
   nos->setTransactTime (Millitime::now ());
   nos->setTimeInForce (Fix50::TimeInForceDayOrSession_0);
   nos->setAccount ("FIXME", nos);

   s->send (nos.getObj ());
}

// The run function sets up the FIX client and initiates the processing

int
run (int argc, const char ** argv)
{
   CmdLine cl (argc, argv, FixClientCmdLine);

   if (cl.printUsageOrValidate ())
      return EXIT_SUCCESS;

   // Set trace level
   
   RuntimeEnv::setLogOpt ("prestofix", "trace", cl.count ("trace"));
   RuntimeEnv::setLogOpt ("fixstate", "trace", cl.count ("trace"));
   
   StrList addresses;
   StrList schemas;
   StrList templates;

   cl.get ("address", addresses);
   cl.get ("schema", schemas);
   cl.get ("templates", templates);

   // Setup the data model. The Presto::DataModel holds meta data
   // about available messages and their structure. The data model is
   // setup by loading FIX Message Schemas (FMS) in XML format.

   StrList libraryPath;
   cl.get ("lib", libraryPath);
   
   DataModel dm (libraryPath);
   dm.loadSchemas (schemas);

   // The initiator is the main controller of the FIX client. It is
   // responsible for creating new sessions and manages them
   // throughout their lifetime.
   //
   // The initiator is parameterized by the following policies:
   //   
   //   TransportPolicy    - Controls how connections are established and how
   //                        bytes are sent and received, and how sessions
   //                        coexist, that is, IO-multiplexing.
   //
   //   MessageStorePolicy - Controls how messages are persisted for
   //                        recovery purposes.
   //
   //   CodecPolicy        - Controls how message are encoded to and decoded
   //                        from the wire representation

   // In this sample application we use file based message journals,
   
   Fix::JournalMessageStore journal;
   journal.setJournalDir (".");

   // and a single-threaded, event driven, transport policy,

   Fix::IoEventLoopTransport evtLoop;

   // and use FIX FAST encoding

   std::auto_ptr <Fix::CodecPolicy> codec;

   if (cl.test ("tv"))
   {
      // Only for debugging purposes
      Fix::TvCodec * tvCodec = new Fix::TvCodec ();
      tvCodec->getParams ().set (NsName ("AllowSendingTimeGracePeriod"), true);
      codec.reset (tvCodec);
   }
   else
   {
      Fix::FastCodec * fastCodec = new Fix::FastCodec ();
      codec.reset (fastCodec);
      fastCodec->loadTemplates (templates);
      fastCodec->setCompatibilityMode ("ngm");
   }
   
   // Instantiate the initiator and set policies. The constructor
   // takes a reference to the data model.

   Fix::Initiator intor (dm);
   intor.setMessageStorePolicy (journal);
   intor.setTransportPolicy (evtLoop);
   intor.setCodecPolicy (*codec);

   // Set the address of the FIX service. Multiple addresses may be
   // specified for failover behavior. Each address is a string on the
   // form "host:port", e.g. "10.0.0.10:8000".
   
   intor.addServerAddresses (addresses);

   // The operation of a fix session is controlled by a number of
   // parameters. These are bundled together in the
   // Fix::Session::Parameters class. The initiator optionally holds a
   // set of default parameters, but parameters may also be set on
   // each individual Fix::Session instance.
   
   Fix::Session::Parameters prms;
   prms.setInitiatorId (cl.get ("initiator"));
   prms.setAcceptorId (cl.get ("acceptor"));
   prms.setUsername (cl.get ("username"));
   prms.setPassword (cl.get ("password"));
   std::string subid;
   if (cl.get ("intorsubid", subid))
      prms.setInitiatorSubId (subid);
   if (cl.get ("actorsubid", subid))
      prms.setAcceptorSubId (subid);
   prms.setFixVersionUri ("FIXT.1.1");
   prms.setHeartBeatInt (Time::Secs (30));
   prms.setResetOnLogon (cl.test ("reset-on-logon"));
   prms.setSendTestRequestOnLogon (true);

   intor.setDefaultSessionParams (prms);

   // Set verbosity level and optionally enable trace events

   Fix::ActivityLogPolicy & logger = intor.getActivityLogPolicy ();
   u32 verbosity;
   if (cl.get ("verbosity", verbosity))
      logger.setVerbosity (verbosity);

   if (cl.test ("trace"))
      logger.enableEvent (Fix::ActivityLogPolicy::EvtTrace);
   
   // Create a sample session

   Fix::Session::Ptr s = intor.newSession ();

   // Register the application message observer. The methods of the
   // observer get called whenever a corresponding message is received

   SampleObs obs (intor);
   s->addObserver (obs);

   // Dump incoming SCP level 2 messages
   
   s->setMethod (& SampleObs::onHello, obs);
   s->setMethod (& SampleObs::onAlert, obs);
   
   // Initiate the session, that is, create a transport and send logon
   
   intor.initiate (s);

   // Interval observers can be added to the event loop to drive
   // application logic. Interval observers get called back
   // recurringly at the specified interval. This example utilizes a
   // convenience template version of the addIntervalObserver method
   // that takes a function (or function object), a user context and
   // the interval time.

   evtLoop.addIntervalObserver (sampleWorker, s, Time::Secs (5));

   // One last thing to do: start the event loop. The event loop will
   // run indefinitely

   evtLoop.run ();

   // and we won't actually get here ...
   
   return EXIT_SUCCESS;
}

// The main function just acts as a wrapper to catch any exceptions,
// the real implementation is in the run function above

int
main (int argc, const char ** argv)
{
   std::ios::sync_with_stdio (false);
   try
   {
      return run (argc, argv);
   }
   catch (const std::exception & e)
   {
      std::cerr << "ERROR: " << e.what () << std::endl;
   }
   catch (...)
   {
      std::cerr << "ERROR: Unknown exception" << std::endl;
   }

   return EXIT_FAILURE;
}
