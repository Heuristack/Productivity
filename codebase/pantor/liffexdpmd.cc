// Copyright (c), Pantor Engineering AB, 1999-2010
// All rights reserved

#include "base/app/CmdLine.h"
#include "presto/fast/LiffeXdpObserver.h"
#include "presto/base/DataModel.h"
#include "presto/mdc/MarketDataClient.h"
#include "presto/if/liffe/gen/PantorLiffeXdpObserver.h"
#include "base/sys/Time.h"
#include "base/io/FdStream.h"
#include "base/text/Tr.h"

using namespace Pantor;
using namespace Xing;
using namespace Presto;

static const char * LiffeXdpMdCmdLine =
   "liffxdpmd [-h/--help]                  # Display this help"
   "          [-L/--lib <dir-or-zip>...]   # Library path for resource lookups"
   "          [-s/--schema <file>...]      # FMS Schema"
   "          [-t/--templates <file>...]   # Template definition in XML"
   "          [-H/--host <host>]           # Host"
   "          [-p/--port <port>]           # Port"
   "          [-l/--local-address <host>]  # Local interface address"
   "          [canned-data]                # Canned data"
   ;
                      
class XdpMsgObs : public Liffe::Xdp::PantorLiffeXdpObserver
{
public:
   XdpMsgObs (const FastDecoder& d) : decoder (d)
   {
   }

   void dump (const Dymo::ObjectSptr & obj)
   {
      decoder.getDataModel ().writeAsText (obj, std::cout);
   }

   void onExchangeMsg (const Liffe::Xdp::ExchangeMsg::Ptr & m) { dump (m); }
   void onMarketStatus (const Liffe::Xdp::MarketStatus::Ptr & m) { dump (m); }
   void onMarketUpdate (const Liffe::Xdp::MarketUpdate::Ptr & m) { dump (m); }
   void onOpenInterest (const Liffe::Xdp::OpenInterest::Ptr & m) { dump (m); }
   void onOptionValuation (
      const Liffe::Xdp::OptionValuation::Ptr & m) { dump (m); }
   void onOutrightStandingData (
      const Liffe::Xdp::OutrightStandingData::Ptr & m) { dump (m); }
   void onProductAvailbility (
      const Liffe::Xdp::ProductAvailbility::Ptr & m) { dump (m); }
   void onSettlementPrices (
      const Liffe::Xdp::SettlementPrices::Ptr & m) { dump (m); }
   void onStrategyStandingData (
      const Liffe::Xdp::StrategyStandingData::Ptr & m) { dump (m); }
   void onValueAddParams (
      const Liffe::Xdp::ValueAddParams::Ptr & m) { dump (m); }
   
private:
   const FastDecoder& decoder;
};

struct XdpPacketObs : public LiffeXdpObserver
{
   void onXdpPacket (const XdpPacket & pkt)
   {
      std::cout << "--- XDP Packet: seqNum=" << pkt.getPacketSeqNum ()
                << " msgCount= " << pkt.getNumberMsgEntries ()
                << " ---\n" << std::endl;

      // Call XdpPacket::decode () to decode the FAST encoded payload

      pkt.decode ();
   };
};

int
run (int argc, const char ** argv)
{
   CmdLine cl (argc, argv, LiffeXdpMdCmdLine);
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
         
   FastDecoder dec (dm, "liffe-xdp");
   dec.loadTemplates (templates);

   Time t1;

   u32 inputSize = 0;
   
   if (cl.has ("host"))
   {
      XdpPacketObs pktObs;
      dec.addExtensionObserver (pktObs);
      
      MarketDataClient mdc (dec);
      XdpMsgObs obs (dec);
      
      dec.addObserver (obs);

      if (cl.has ("port"))
      {
         t1 = Time::Now;
         mdc.join (cl.get ("host"), port, cl.get ("local-address"));
      }
      else
         throw RuntimeException ("Missing port parameter");
   }
   else if (cl.has ("canned-data"))
   {
      static const u32 ChunkSize = 8192;
      std::vector<u8> data;
      FdStream is (cl.get ("canned-data"), FdStream::READ);

      for (;;)
      {
         data.resize (inputSize + ChunkSize);
         u32 n = is.read (& data [inputSize], ChunkSize);
         inputSize += n;
         if (n < ChunkSize)
         {
            data.resize (inputSize);
            break;
         }
      }

      t1 = Time::Now;
      
      for (const u8 * p = & data.front (), * e = p + inputSize; p < e;)
      {
         u32 packetSize = *reinterpret_cast <const u32 *> (p);
         p += sizeof (u32);
         dec.decode (p, packetSize);
         p += packetSize + sizeof (u64) /* tsp? */;
      }
   }
   else
      throw RuntimeException ("No canned data or host specified");
   

   Time::Delta elapsed = Time (Time::Now) - t1;

   i64 ms = elapsed.getMillisecs ();

   u32 msgCount = dec.getMsgCount ();

   std::cout
      << msgCount << " messages processed in "
      << ms << "ms (wall clock), "
      << std::setprecision (3) << std::fixed
      << u64 (f64 (msgCount) / (f64 (ms) / 1000)) << "msg/s" << std::endl;

   if (inputSize > 0)
      std::cout << "Bandwidth: "
                << std::setprecision (3) << std::fixed
                << Tr::toHumanStr (u64 (f64 (inputSize) / (f64 (ms) / 1000)))
                << "B/s" << std::endl;

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
