// Copyright (c), Pantor Engineering AB, 1999-2010
// All rights reserved

#include "base/app/CmdLine.h"
#include "presto/fast/ArcaObserver.h"
#include "presto/base/DataModel.h"
#include "presto/mdc/MarketDataClient.h"
#include "presto/if/arca/gen/NyseArcaObserver.h"
#include "base/sys/Time.h"

using namespace Pantor;
using namespace Xing;
using namespace Presto;

static const char * ArcaMdCmdLine =
   "arcamd [-h/--help]                  # Display this help"
   "       [-L/--lib <dir-or-zip>...]   # Library path for resource lookups"
   "       [-s/--schema <file>...]      # FMS Schema"
   "       [-t/--templates <file>...]   # Template definition in XML"
   "       -H/--host <host>             # Host"
   "       -p/--port <port>             # Port"
   "       [-l/--local-address <host>]  # Local interface address"
   ;
                      
class ArcaMsgObs : public Nyse::Arca::NyseArcaObserver
{
public:
   ArcaMsgObs (const FastDecoder& d)
      : decoder (d), msgCount (0)
   {
   }

   void dump (const Dymo::ObjectSptr & obj)
   {
      ++ msgCount;
      decoder.getDataModel ().writeAsText (obj, std::cout);
   }

   void onAddOrder (const Nyse::Arca::AddOrder::Ptr & m) { dump (m); }
   void onBookRefresh (const Nyse::Arca::BookRefresh::Ptr & m) { dump (m); }
   void onBookRefreshRequest (
      const Nyse::Arca::BookRefreshRequest::Ptr & m) { dump (m); }
   void onDeleteOrder (const Nyse::Arca::DeleteOrder::Ptr & m) { dump (m); }
   void onFirmIndexMapping (
      const Nyse::Arca::FirmIndexMapping::Ptr & m) { dump (m); }
   void onFirmIndexMappingRequest (
      const Nyse::Arca::FirmIndexMappingRequest::Ptr & m) { dump (m); }
   void onGenericBook (const Nyse::Arca::GenericBook::Ptr & m) { dump (m); }
   void onHeartbeat (const Nyse::Arca::Heartbeat::Ptr & m) { dump (m); }
   void onHeartbeatResponse (const Nyse::Arca::HeartbeatResponse::Ptr & m) {
      dump (m); }
   void onImbalance (const Nyse::Arca::Imbalance::Ptr & m) { dump (m); }
   void onImbalanceRefresh (
      const Nyse::Arca::ImbalanceRefresh::Ptr & m) { dump (m); }
   void onImbalanceRefreshRequest (
      const Nyse::Arca::ImbalanceRefreshRequest::Ptr & m) { dump (m); }
   void onMessageUnavailable (
      const Nyse::Arca::MessageUnavailable::Ptr & m) { dump (m); }
   void onModifyOrder (const Nyse::Arca::ModifyOrder::Ptr & m) { dump (m); }
   void onRetransmissionRequest (
      const Nyse::Arca::RetransmissionRequest::Ptr & m) { dump (m); }
   void onRetransmissionResponse (
      const Nyse::Arca::RetransmissionResponse::Ptr & m) { dump (m); }
   void onSequenceNumberReset (
      const Nyse::Arca::SequenceNumberReset::Ptr & m) { dump (m); }
   void onSymbolClear (const Nyse::Arca::SymbolClear::Ptr & m) { dump (m); }
   void onSymbolIndexMapping (
      const Nyse::Arca::SymbolIndexMapping::Ptr & m) { dump (m); }
   void onSymbolIndexMappingRequest (
      const Nyse::Arca::SymbolIndexMappingRequest::Ptr & m) { dump (m); }

   u32 getMsgCount () const { return msgCount; }
   
private:
   const FastDecoder& decoder;
   u32 msgCount;
};

struct ArcaPacketObs : public ArcaObserver
{
   void onArcaPacket (const ArcaPacket & pkt)
   {
      std::cout << "--- ARCA Packet: seqNum=" << pkt.getMsgSeqNum ()
                << " msgCount= " << pkt.getNumBodyEntries ()
                << " ---\n" << std::endl;

      // Call ArcaPacket::decode () to decode the FAST encoded payload

      pkt.decode ();
   };
};

int
run (int argc, const char ** argv)
{
   CmdLine cl (argc, argv, ArcaMdCmdLine);
   if (cl.printUsageOrValidate ())
      return EXIT_SUCCESS;

   u32 port;
   cl.get ("port", port);
   
   StrList resourceLibs;
   cl.get ("lib", resourceLibs);

   StrList schemas;
   cl.get ("schema", schemas);

   StrList templates;
   cl.get ("templates", templates);

   DataModel dm (resourceLibs);
   dm.loadSchemas (schemas);
         
   FastDecoder dec (dm, "arca");
   ArcaPacketObs pktObs;
   dec.addExtensionObserver (pktObs);
      
   MarketDataClient mdc (dec);
   ArcaMsgObs obs (dec);

   dec.addObserver (obs);
   dec.loadTemplates (templates);

   Time t1 (Time::Now);
      
   mdc.join (cl.get ("host"), port, cl.get ("local-address"));

   Time::Delta elapsed = Time (Time::Now) - t1;

   std::cout
      << obs.getMsgCount () << " messages processed in "
      << elapsed.getMillisecs () << "ms (wall clock)" 
      << std::endl;

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
