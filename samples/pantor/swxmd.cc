// Copyright (c), Pantor Engineering AB, 1999-
// All rights reserved

#include "base/app/CmdLine.h"
#include "presto/fast/SwxObserver.h"
#include "presto/base/DataModel.h"
#include "presto/mdc/MarketDataClient.h"
#include "presto/mdc/McTap.h"
#include "presto/if/swx/gen/Fix50Observer.h"
#include "presto/if/swx/gen/FixT11Observer.h"
#include "presto/if/swx/gen/Fix50TypeInfo.h"
#include "base/text/StrUtils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#if ! defined (OS_win)
#include <unistd.h>
#endif

using namespace Pantor;
using namespace Xing;
using namespace Fix50;
using namespace FixT11;
using namespace Presto;

static const char * SwxMdCmdLine =
   "swxmd [-h/--help]                  # Display this help"
   "      mode                         # Mode is one of 'ipmcdump',"
   "                                   # 'ipmcstats', 'dump', 'stats',"
   "                                   # 'bufdump', 'bufstats' and 'tap'"
   "      [-L/--lib <dir-or-zip>...]   # Library path for resource lookups"
   "      [-s/--schema <file>...]      # FMS Schema"
   "      [-t/--templates <file>...]   # Template definition in XML"
   "      [-H/--host <host>]           # Host"
   "      [-p/--port <port>]           # Port"
   "      [-l/--local-address <host>]  # Local interface address"
   "      [-o/--output <file>]         # Write tapped messages to file"
   "      [-c/--count <num>]           # Number of messages to tap before"
   "                                   # exiting"
   "      [input]                      # Input FAST file"
   ;
                      
static void
printHeader (const std::string & nm, const FixT11::Envelope & e)
{
   std::cout << nm << ": "
             << "seqNum=" << e.getMsgSeqNum ()
             << ", sender=\"" << e.getSenderCompID ().toString () << "\""
             << ", tsp=" << e.getSendingTime () << std::endl;
}

// Example on how to save messages until you are done with them.
// A Message::Ptr is a referenced counted smart pointer.
// By keeping a reference to the message, it will stay around until
// the last reference goes away.

static MarketDataIncrementalRefresh::Ptr lastIncremental;

class StatsFix50Observer : public Fix50Observer
{
public:
   StatsFix50Observer ()
      : msgs (0)
   {
   }
   
   void onNews (const News::Ptr &)
   {
      ++ msgs;
   }
  
   void onMarketDataIncrementalRefresh (
      const MarketDataIncrementalRefresh::Ptr & m)
   {
      ++ msgs;
      lastIncremental = m;
   }

   void onMarketDataSnapshotFullRefresh (
      const MarketDataSnapshotFullRefresh::Ptr &)
   {
      ++ msgs;
   }

   void onSecurityStatus (const SecurityStatus::Ptr & m)
   {
      // Demonstration of casting functionality
      // The message object can be stored polymorphically, for instance
      // using a std::vector<FixT11::Envelope::Ptr>.
      // Here we assign a base class similarly to how it would be added
      // to the container
      
      FixT11::Envelope::Ptr base = m;

      // Instead of using dynamic_cast, the Xing::safeCast method
      // is used to downcast to the actual type. safeCast does
      // validation of the internal data type
      
      SecurityStatus::Ptr m2 =
         Xing::safeCast <const SecurityStatus::Ptr&> (base);
      
      ++ msgs;
   }

   u32 getMessageCount () const { return msgs; }
   
private:
   u32 msgs;
};

class StatsT11Observer : public FixT11Observer
{
public:
   StatsT11Observer ()
      : msgs (0)
   {
   }
   void onLogon (const Logon::Ptr &)
   {
      ++ msgs;
   }

   void onLogout (const Logout::Ptr & m)
   {
      ++ msgs;
      printHeader ("Logout", *m);
      if (m->getText () != NULL)
         std::cout << "text=" << m->getText ()->toString () << std::endl;
   }

   void onHeartbeat (const Heartbeat::Ptr & m)
   {
      ++ msgs;
      printHeader ("Heartbeat", *m);
   }

   u32 getMessageCount () const { return msgs; }
   
private:
   u32 msgs;
};

static inline void
dump (const FastDecoder & dec, const Dymo::ObjectSptr & obj)
{
   dec.getDataModel ().writeAsText (obj, std::cout);
}

class DumpFix50Observer : public StatsFix50Observer
{
public:
   DumpFix50Observer (const FastDecoder& d)
      : decoder (d)
   {
   }
   
   void onNews (const News::Ptr & m)
   {
      StatsFix50Observer::onNews (m);
      printHeader ("News", *m);
   }

   void onMarketDataIncrementalRefresh (
      const MarketDataIncrementalRefresh::Ptr & m)
   {
      StatsFix50Observer::onMarketDataIncrementalRefresh (m);
      dump (decoder, m);
   }

   void onMarketDataSnapshotFullRefresh (
      const MarketDataSnapshotFullRefresh::Ptr & m)
   {
      StatsFix50Observer::onMarketDataSnapshotFullRefresh (m);
      dump (decoder, m);
   }

   void onSecurityStatus (const SecurityStatus::Ptr & m)
   {
      StatsFix50Observer::onSecurityStatus (m);
      dump (decoder, m);
   }

private:
   const FastDecoder& decoder;
};

class DumpT11Observer : public StatsT11Observer
{
public:
   DumpT11Observer (const FastDecoder& d)
      : decoder (d)
   {
   }

   void onLogon (const Logon::Ptr & m)
   {
      StatsT11Observer::onLogon (m);
      dump (decoder, m);
   }

   void onLogout (const Logout::Ptr & m)
   {
      StatsT11Observer::onLogout (m);
      dump (decoder, m);
   }

   void onHeartbeat (const Heartbeat::Ptr & m)
   {
      StatsT11Observer::onHeartbeat (m);
      dump (decoder, m);
   }
   
private:
   const FastDecoder& decoder;
};

struct SwxObs : public SwxObserver
{
   void onSwxPacket (const SwxPacket & pkt)
   {
      std::cout << "--- SWX Packet: seqNum=" << pkt.getSeqNum () << " ---\n"
                << std::endl;

      // Call SwxPacket::decode () to decode the FAST encoded payload

      pkt.decode ();
   };
};

static inline u32
getPort (const CmdLine & cl)
{
   u32 port;
   if (! cl.get ("port", port))
      throw RuntimeException ("No port specified");
   return port;
}

int
run (int argc, const char ** argv)
{
   CmdLine cl (argc, argv, SwxMdCmdLine);
   if (cl.printUsageOrValidate ())
      return EXIT_SUCCESS;

   std::string mode = cl.get ("mode");

   if (mode == "tap")
   {
      // Join IP MC and output to file.
      // No decoding of FAST messages takes place.

      u32 count = 0; // Zero means unlimited tapping
      cl.get ("count", count);
      McTap::tap (cl.get ("host"), getPort (cl), cl.get ("local-address"),
                  cl.get ("output"), count);
   }
   else
   {
      StrList resourceLibs;
      cl.get ("lib", resourceLibs);

      StrList schemas;
      cl.get ("schema", schemas);

      StrList templates;
      cl.get ("templates", templates);

      DataModel dm (resourceLibs);
      dm.loadSchemas (schemas);
         
      FastDecoder dec (dm, "swx");
      SwxObs swx;
      dec.addExtensionObserver (swx);
      
      MarketDataClient mdc (dec);
      std::auto_ptr <StatsFix50Observer> observer;
      std::auto_ptr <StatsT11Observer> t11Observer;

      if (StrUtils::contains (mode, "dump"))
      {
         observer.reset (new DumpFix50Observer (dec));
         t11Observer.reset (new DumpT11Observer (dec));
      }
      else
      {
         observer.reset (new StatsFix50Observer ());
         t11Observer.reset (new StatsT11Observer ());
      }
      
      dec.addObserver (* observer);
      dec.addObserver (* t11Observer);
      
      dec.loadTemplates (templates);

      Nanotime start = Nanotime::now ();
      
      if (StrUtils::startsWith (mode, "ipmc"))
         // MarketDataClient can also join an IP Multicast stream
         mdc.join (cl.get ("host"), getPort (cl), cl.get ("local-address"));
      else if (StrUtils::startsWith (mode, "buf"))
      {
         // FastDecoder has a more raw interface that is demonstrated here
         int fd = ::open (cl.get ("input").c_str (), O_RDONLY);
         u8 buf [8192];
         
         for (;;)
         {
            u32 n = ::read (fd, (char*) buf, sizeof (buf));
            dec.decode (buf, n);
            if (n < sizeof (buf))
               break;
         }
      }
      else
      {
         // SingleResettingBlock only works in packet oriented
         // processing, use ResettingBlock mode when reading from
         // file
         dec.setBlockMode (FastDecoder::ResettingBlock);
         mdc.decode (cl.get ("input"));
      }

      Nanotime delta = Nanotime::now () - start;

      if (lastIncremental != 0)
      {
         std::cout << "Last incremental: seqNum="
                   << lastIncremental->getMsgSeqNum ()
                   << std::endl;
      }
         
      std::cout
         << observer->getMessageCount () + t11Observer->getMessageCount ()
         << " messages processed in "
         << delta.getMilli () << "ms (wall clock)" 
         << std::endl;

      if (mdc.getAggregatedDecodeTime ().isSet ())
         std::cout << "Aggregated decode time: "
                   << mdc.getAggregatedDecodeTime ().getMilli ()
                   << "ms" << std::endl;
   }

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
