// Copyright (c), Pantor Engineering AB, 1999-2011
// All rights reserved

///////////////////////////////////////////////////////////////////////////
//
//   This is a sample FIX client that gives an overview of the basic
//   features of the Presto FIX library. The sample shows how to setup
//   an initiator and how to send and receive FIX messages using the
//   dynamic capabilities of presto.
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
#include "base/dymo/Schema.h"
#include "base/dymo/Builder.h"
#include "base/dymo/NsNameObsRegistry.h"

using namespace Pantor;
using namespace Presto;

// Command line specification

static const char * CmdLineSpec =
   "dynfix [-h/--help]                     # Display this help"
   "       [-L/--lib <dir-or-jar>...]      # Resource library path"
   "       -a/--address <host:port>...     # Hosts and ports"
   "       -s/--schema <schema-file>...    # FMS Schema"
   "       -I/--initiator <sender-comp-id> # SenderCompID"
   "       -A/--acceptor <target-comp-id>  # TargetCompID"
   "       [-v/--verbosity <level>]        # Verbosity level"
   "       [-t/--trace...]                 # Trace level"
   "       [-r/--reset-on-logon]           # Reset seqNum to 1 on logon"
   "       [-V/--fix-version <version>]    # Fix version. E.g '4.3'"
   "                                       # If not specified, the data"
   "                                       # model must contain a single"
   "                                       # version. If version is >= 5.0,"
   "                                       # then FIXT.1.1 is used as the"
   "                                       # session version"
   ;


// The sample worker sends a NewOrderSingle every five seconds if the
// session is on-line and dumps any incoming execution reports

struct SampleWorker
{
   // The constructor sets up the necessary definitions for populating
   // a new order single. The metadata is fetched through helper functions
   // to deal with error handling
   
   SampleWorker (const DataModel & dm_, const Fix::Session::Ptr & session_)
      : dm (dm_), nosDef (getGroup ("NewOrderSingle")),
        pxDef (getField (nosDef, "Price")),
        sideDef (getField (nosDef, "Side")),
        symDef (getField (nosDef, "Symbol")),
        transactTimeDef (getField (nosDef, "TransactTime")),
        clOrdIdDef (getField (nosDef, "ClOrdID")),
        ptysDef (getField (nosDef, "PartyIDs")),
        ptyIdDef (getField (ptysDef.getTypeDef ().getInnerGroupDef (),
                            "PartyID")),
        sideBuy (getEnumSym ("Side", "Buy_1")),
        session (session_)
   {
   }

   // Helper function for retrieving a group definition from the data model
   
   const Dymo::GroupDef & getGroup (const std::string & name)
   {
      const Dymo::GroupDef * g = dm.getSchema ().getGroup (name);
      if (g == NULL)
         throw RuntimeException ("Cannot find group type in data model: " +
                                 name);
      else
         return *g;
   }

   // Helper function for retrieving a field definition from a group definition

   const Dymo::FieldDef & getField (const Dymo::GroupDef & grp,
                                    const std::string & name)
   {
      const Dymo::FieldDef * f = grp.getField (name);
      if (f == NULL)
         throw RuntimeException ("No such field: " + grp.getQualifiedName () +
                                 "." + name);
      else
         return *f;
   }

   const Dymo::FieldDef & getField (const Dymo::GroupDef * grp,
                                    const std::string & name)
   {
      if (grp == NULL)
         throw RuntimeException ("Missing subgroup");
      else
         return getField (*grp, name);
   }

   // Helper function for retrieving an enum symbol

   i32 getEnumSym (const std::string & enm, const std::string & sym)
   {
      const Dymo::Define * def = dm.getSchema ().getDefine (enm);
      const Dymo::EnumTypeDef * etd = NULL;
      if (def != NULL)
         etd = dynamic_cast <const Dymo::EnumTypeDef *> (& def->getTypeDef ());

      if (etd != NULL)
      {
         i32 pos;
         if (etd->getSymbolPos (StrRef (sym), pos))
            return pos;
         else
            throw RuntimeException ("No such enum symbol: " + enm + "." + sym);
      }
      else
         throw RuntimeException ("No such enum: " + enm);
   }
   
   // onExecutionReport gets called whenever an execution report
   // arrives. In this sample implementation we just dump the ER as
   // text to the standard error stream.
   
   void onExecutionReport (const Dymo::ObjectSptr & er)
   {
      dm.writeAsText (er, std::cerr);
   }

   void doWork ()
   {
      if (! session->isLoggedOn () || ! session->isConnected ())
      {
         session->log ("Not logged on or not connected, retrying ...");
         return;
      }
   
      // Create and send a NewOrderSingle

      Dymo::Builder b;
      b.startObj (nosDef);

      b.cur ().setDec (pxDef, Decimal (17));
      b.setStr (clOrdIdDef, "4711");
      b.setStr (symDef, "CPNY");

      b.cur ().setMilli (transactTimeDef, Millitime::now ());

      // An enum is treated as an i32 in the memory model
      
      b.cur ().setI32 (sideDef, sideBuy);

      // Create a sequence with two items
      
      b.startSeq (ptysDef, 2);

      // Now the builder is positioned at the first subgroup
      
      b.setStr (ptyIdDef, "FirstPty");

      // Advance the builder to next item

      b.nextSeqElm ();
      b.setStr (ptyIdDef, "SecondPty");

      // Close the sequence
      
      b.endSeq ();
      
      // Close the NOS object
      
      Dymo::ObjectSptr nos = b.endObj ();

      // Send the NOS on the session
      
      session->send (nos);
   }
   
   const DataModel & dm;
   const Dymo::GroupDef & nosDef;
   const Dymo::FieldDef & pxDef;
   const Dymo::FieldDef & sideDef;
   const Dymo::FieldDef & symDef;
   const Dymo::FieldDef & transactTimeDef;
   const Dymo::FieldDef & clOrdIdDef;
   const Dymo::FieldDef & ptysDef;
   const Dymo::FieldDef & ptyIdDef;
   i32 sideBuy;
   Fix::Session::Ptr session;
};


void doWork (Fix::IoEventLoopTransport::IntervalControl &, SampleWorker & w)
{
   w.doWork ();
}

// The run function sets up the FIX client and initiates the processing

int
run (int argc, const char ** argv)
{
   CmdLine cl (argc, argv, CmdLineSpec);

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

   // Register methods of the worker to observe specific messages. The
   // methods of the observer get called whenever a corresponding
   // message is received. The methods are registered via an observer
   // registry which in turn is installed in the session.

   SampleWorker worker (intor.getDataModel (), s);

   Dymo::NsNameObsRegistry oreg;

   oreg.setMethod (&SampleWorker::onExecutionReport, worker,
                   "ExecutionReport");
   
   s->addObserverRegistry (oreg);
   
   // Initiate the session, that is, create a transport and send logon
   
   intor.initiate (s);

   // Interval observers can be added to the event loop to drive
   // application logic. Interval observers get called back
   // recurringly at the specified interval. This example utilizes a
   // convenience template version of the addIntervalObserver method
   // that takes a function (or function object), a user context and
   // the interval time.
   
   evtLoop.addIntervalObserver (doWork, worker, Time::Secs (5));

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
