// Copyright (c), Pantor Engineering AB, 1999-
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
#include "presto/fix/TvCodec.h"
#include "presto/fix/Initiator.h"
#include "presto/fix/ActivityLogPolicy.h"
#include "base/xymo/Alloc.h"

#include "presto/if/fix/gen/Fix43Observer.h"

using namespace Pantor;
using namespace Presto;

// Command line specification

static const char * FixClientCmdLine =
   "fixclient [-h/--help]                     # Display this help"
   "          [-L/--lib <dir-or-jar>...]      # Resource library path"
   "          -a/--address <host:port>...     # Hosts and ports"
   "          -s/--schema <schema-file>...    # FMS Schema"
   "          -I/--initiator <sender-comp-id> # SenderCompID"
   "          -A/--acceptor <target-comp-id>  # TargetCompID"
   "          [-P/--password <password>]      # Password"
   "          [-N/--new-password <password>]  # New Password"
   "          [-v/--verbosity <level>]        # Verbosity level"
   "          [-t/--trace...]                 # Trace level"
   "          [-r/--reset-on-logon]           # Reset seqNum to 1 on logon"
   "          [-V/--fix-version <version>]    # Fix version. E.g '4.3'"
   "                                          # If not specified, the data"
   "                                          # model must contain a single"
   "                                          # version. If version is >= 5.0,"
   "                                          # then FIXT.1.1 is used as the"
   "                                          # session version"
   ;


// The sample observer observs execution reports

struct SampleObs : public Fix43::Fix43Observer
{
   SampleObs (const Fix::Initiator & intor_) : intor (intor_) { }

   // onExecutionReport gets called whenever an execution report
   // arrives. In this sample implementation we just dump the ER as
   // text to the standard error stream.
   
   void onExecutionReport (const Fix43::ExecutionReport::Ptr & er)
   {
      intor.getDataModel ().writeAsText (er, std::cerr);
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

   Xing::ObjHandle<Fix43::NewOrderSingle> nos;
   nos->setClOrdID ("FIXME", nos);
   nos->setOrdType (Fix43::OrdTypeMarket_1);
   nos->setExDestination ("FIXME", nos);
   nos->setSecurityID ("FIXME", nos);
   nos->setCurrency ("FIXME", nos);
   nos->setSecurityIDSource (Fix43::SecurityIDSourceIsinNumber_4);
   nos->setOrderQty (Decimal (100));
   nos->setPrice (Decimal (17));
   nos->setSide (Fix43::SideBuy_1);
   nos->setTransactTime (Millitime::now ());
   nos->setTimeInForce (Fix43::TimeInForceDay_0);
   nos->setSymbol ("Symbol", nos);
   
   nos->createPartyIDs (1, nos);
   Xing::Handle<Fix43::PartiesPartyIDs> pty ((* nos->getPartyIDs ()) [0], nos);

   pty->setPartyID ("FIXME", nos);
   pty->setPartyIDSource (Fix43::PartyIDSourceProprietary_D);
   pty->setPartyRole (Fix43::PartyRoleOrderOriginationTrader_11);

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

   cl.get ("address", addresses);
   cl.get ("schema", schemas);

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

   // and use FIX tag/value encoding

   Fix::TvCodec tvCodec;
   
   // Instantiate the initiator and set policies. The constructor
   // takes a reference to the data model.

   Fix::Initiator intor (dm);
   intor.setMessageStorePolicy (journal);
   intor.setTransportPolicy (evtLoop);
   intor.setCodecPolicy (tvCodec);

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
   prms.setFixVersionUri (cl.get ("fix-version"));
   prms.setResetOnLogon (cl.test ("reset-on-logon"));
   prms.setPassword (cl.get ("password"));
   prms.setNewPassword (cl.get ("new-password"));
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
