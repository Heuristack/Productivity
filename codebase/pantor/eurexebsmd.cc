// $Id$

// Copyright (c), Pantor Engineering AB, 1999-2008
// All rights reserved

#include "base/xymo/UnionObserver.h"
#include "presto/mdc/MarketDataClient.h"
#include "presto/mdc/McTap.h"
#include "presto/if/eurex/gen/Eurex14EbsObserver.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#if ! defined (OS_win)
#include <unistd.h>
#endif

using namespace Pantor;
using namespace Xing; // Pantor mechanism that performs messages dispatching
using namespace Presto;

namespace EEBS14 = Eurex14::Ebs;

namespace Eurex14 { namespace Ebs {
      typedef Eurex14EbsObserver Observer;
}}


class StatsObserver : public EEBS14::Observer
{
public:
   StatsObserver (FastDecoder& dec)
      : decoder (dec), msgs (0)
   {
   }
   
   u32 getMessageCount () const { return msgs; }
   
   void onadditionalcontractinformationmessage (
      const EEBS14::additionalcontractinformationmessage::Ptr &)
   {
      ++ msgs;
   }
   
   void onbeaconmessage (
      const EEBS14::beaconmessage::Ptr &)
   {
      ++ msgs;
   }
   
   void onblockauctionstatus (
      const EEBS14::blockauctionstatus::Ptr &)
   {
      ++ msgs;
   }
   
   void onendproductreferenceinformation (
      const EEBS14::endproductreferenceinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onendservice (
      const EEBS14::endservice::Ptr &)
   {
      ++ msgs;
   }
   
   void onendsinglelegreferenceinformation (
      const EEBS14::endsinglelegreferenceinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onendsinglelegsnapshotinformation (
      const EEBS14::endsinglelegsnapshotinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onendstrategyreferenceinformation (
      const EEBS14::endstrategyreferenceinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onendstrategysnapshotinformation (
      const EEBS14::endstrategysnapshotinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onorderbookdeltamessage (
      const EEBS14::orderbookdeltamessage::Ptr &)
   {
      ++ msgs;
   }
   
   void onorderbooksnapshotmessage (
      const EEBS14::orderbooksnapshotmessage::Ptr &)
   {
      ++ msgs;
   }
   
   void onproductreferencemessage (
      const EEBS14::productreferencemessage::Ptr &)
   {
      ++ msgs;
   }
#if 0   
   void onproductstatusmessage (
      const EEBS14::productstatusmessage::Ptr &)
   {
      ++ msgs;
   }
#endif
   
   void onrequestmessage (
      const EEBS14::requestmessage::Ptr &)
   {
      ++ msgs;
   }
   
   void onsinglelegreferencemessage (
      const EEBS14::singlelegreferencemessage::Ptr &)
   {
      ++ msgs;
   }
   
   void onstartproductreferenceinformation (
      const EEBS14::startproductreferenceinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onstartservice (
      const EEBS14::startservice::Ptr &)
   {
      ++ msgs;
   }
   
   void onstartsinglelegreferenceinformation (
      const EEBS14::startsinglelegreferenceinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onstartsinglelegsnapshotinformation (
      const EEBS14::startsinglelegsnapshotinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onstartstrategyreferenceinformation (
      const EEBS14::startstrategyreferenceinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onstartstrategysnapshotinformation (
      const EEBS14::startstrategysnapshotinformation::Ptr &)
   {
      ++ msgs;
   }
   
   void onstrategyreferencemessage (
      const EEBS14::strategyreferencemessage::Ptr &)
   {
      ++ msgs;
   }
   
   void ontrademessage (
      const EEBS14::trademessage::Ptr &)
   {
      ++ msgs;
   }
   
protected:
   FastDecoder& decoder;

private:
   u32 msgs;
};

class DumpObserver : public StatsObserver
{
public:
   DumpObserver (FastDecoder& dec)
      : StatsObserver (dec), verbose (false)
   {}
   
   void setVerbose (bool flag)
   {
      verbose = flag;
   }

   template <typename T>
   void dumpFirst (const T& m, const std::string& msg)
   {
      std::cerr << msg;
      if (verbose)
         std::cerr << " tsp=" << m->getTimestamp ()
                   << " srcId=" << m->getSrcId ();
   }

   void dumpFirst (const EEBS14::orderbookdeltamessage::Ptr &,
                   const std::string& msg)
   {
      std::cerr << msg;
   }

   template <typename T>
   void dumpIdent (const ObjectSptr<T>& m)
   {
      if (! verbose)
         return;
      
      const EEBS14::contractDescription* cd = m->getContractDescription ();
      if (cd != NULL)
         std::cerr << " cntrId=" << cd->getCntrId ();

      const EEBS14::strategyDescription* sd = m->getStrategyDescription ();
      if (sd != NULL)
      {
         std::cerr << " prodId=" << sd->getProdId ()
                   << " stratType=" << sd->getStratType ()
                   << " undrPrc=" << sd->getUndrPrc ();

         const Sequence<EEBS14::strategyDescription::strategyLegs>& legs =
            sd->getStrategyLegs ();
         for (u32 i = 0; i < legs.size (); i ++)
         {
            const EEBS14::strategyDescription::strategyLegs& l = legs [i];
            std::cerr << " [leg" << i+1 << ":"
                      << " cntrId=" << l.getStratCntrId ()
                      << " buySellCode=" << l.getStratBuySellCode ()
                      << " vol=" << l.getStratLegVol ()
                      << "]";
         }
      }
   }


   void onadditionalcontractinformationmessage (
      const EEBS14::additionalcontractinformationmessage::Ptr & m)
   {
      StatsObserver::onadditionalcontractinformationmessage (m);
      std::cerr << "onadditionalcontractinformationmessage v14" << std::endl;
   }
   
   void onbeaconmessage (
      const EEBS14::beaconmessage::Ptr & m)
   {
      StatsObserver::onbeaconmessage (m);
      dumpFirst (m, "onbeaconmessage v14");
      dumpIdent (m);
      if (verbose)
         std::cerr << " lastSeqNum1=" << m->getLastSeqNum1 ()
                   << " lastSeqNum2=" << m->getLastSeqNum2 ();
      std::cerr << std::endl;
   }
   
   void onblockauctionstatus (
      const EEBS14::blockauctionstatus::Ptr & m)
   {
      StatsObserver::onblockauctionstatus (m);
      std::cerr << "onblockauctionstatus v14" << std::endl;
   }
   
   void onendproductreferenceinformation (
      const EEBS14::endproductreferenceinformation::Ptr & m)
   {
      StatsObserver::onendproductreferenceinformation (m);
      std::cerr << "onendproductreferenceinformation v14" << std::endl;
   }
   
   void onendservice (
      const EEBS14::endservice::Ptr & m)
   {
      StatsObserver::onendservice (m);
      std::cerr << "onendservice v14" << std::endl;
   }
   
   void onendsinglelegreferenceinformation (
      const EEBS14::endsinglelegreferenceinformation::Ptr & m)
   {
      StatsObserver::onendsinglelegreferenceinformation (m);
      std::cerr << "onendsinglelegreferenceinformation v14";
      if (verbose)
      {
         std::cerr << " tsp=" << m->getTimestamp ()
                   << " mode=" << m->getMode ()

                   << " busDate=" << m->getBusDate ()
                   << " noOfMsgs=" << m->getNoOfMsgs ();
      }
      std::cerr << std::endl;
   }
   
   void onendsinglelegsnapshotinformation (
      const EEBS14::endsinglelegsnapshotinformation::Ptr & m)
   {
      StatsObserver::onendsinglelegsnapshotinformation (m);
      std::cerr << "onendsinglelegsnapshotinformation v14";
      if (verbose)
      {
         std::cerr << " tsp=" << m->getTimestamp ();
         if (m->getProdId ())
            std::cerr << " prodId=" << *m->getProdId ();
         if (m->getNoOfMsgs ())
            std::cerr << " noOfMsgs=" << *m->getNoOfMsgs ();
      }
      std::cerr << std::endl;
   }
   
   void onendstrategyreferenceinformation (
      const EEBS14::endstrategyreferenceinformation::Ptr & m)
   {
      StatsObserver::onendstrategyreferenceinformation (m);
      std::cerr << "onendstrategyreferenceinformation v14";
      if (verbose)
      {
         std::cerr << " tsp=" << m->getTimestamp ()
                   << " mode=" << m->getMode ()
                   << " busDate=" << m->getBusDate ()
                   << " noOfMsgs=" << m->getNoOfMsgs ();
      }
      std::cerr << std::endl;
   }
   
   void onendstrategysnapshotinformation (
      const EEBS14::endstrategysnapshotinformation::Ptr & m)
   {
      StatsObserver::onendstrategysnapshotinformation (m);
      std::cerr << "onendstrategysnapshotinformation v14";
      if (verbose)
      {
         std::cerr << " tsp=" << m->getTimestamp ();
         if (m->getProdId () != NULL)
            std::cerr << " prodId=" << *m->getProdId ();
         if (m->getNoOfMsgs () != NULL)
            std::cerr << " noOfMsgs=" << *m->getNoOfMsgs ();
      }
      std::cerr << std::endl;
   }
   
   void onorderbookdeltamessage (
      const EEBS14::orderbookdeltamessage::Ptr & m)
   {
      StatsObserver::onorderbookdeltamessage (m);
      dumpFirst (m, "onorderbookdeltamessage v14");
      if (verbose)
      {
         std::cerr << " seqNum=" << m->getSeqNum ();
         if (m->getLinkedBrcastId () != NULL)
            std::cerr << " BID=" << *m->getLinkedBrcastId ();
         if (m->getLbiChannelMap () != NULL)
            std::cerr << " chMap=" << *m->getLbiChannelMap ();
         if (m->getLastTpSeqNum () != NULL)
            std::cerr << " lastTpSeqNum=" << *m->getLastTpSeqNum ();
         
         dumpIdent (m);
         
         if (m->getGapIndicator () != NULL && * m->getGapIndicator () == "2")
            std::cerr << " GAP";
         
         if (m->getDlyHghPrc () != NULL)
            std::cerr << " dlyHghPrc=" << *m->getDlyHghPrc ();
         if (m->getDlyLowPrc () != NULL)
            std::cerr << " dlyLowPrc=" << *m->getDlyLowPrc ();
         if (m->getTotTrdQty () != NULL)
            std::cerr << " totTrdQty=" << *m->getTotTrdQty ();
#if 0
         if (m->getCntrStatus () != NULL)
            std::cerr << " cntrStatus=" << *m->getCntrStatus ();
#endif
         
         const Sequence<EEBS14::orderbookdeltamessage::entries>& lvls =
            m->getEntries ();
         if (! lvls.empty ())
         {
            std::cerr << " lvl 1/" << lvls.size () << ":"
                      << " updAction=" << lvls [0].getUpdateAction ()
                      << " type=" << lvls [0].getEntryType ();
            if (lvls [0].getEntryPrcLvl () != NULL)
               std::cerr << " lvl=" << *lvls [0].getEntryPrcLvl ();
            std::cerr << " prc=" << lvls [0].getEntryPrc ()
                      << " qty=" << lvls [0].getEntryQty ();
            if (lvls [0].getEntryPrcSrc () != NULL)
               std::cerr << " src=" << *lvls [0].getEntryPrcSrc ();
         }
      }
      std::cerr << std::endl;
   }
   
   void onorderbooksnapshotmessage (
      const EEBS14::orderbooksnapshotmessage::Ptr & m)
   {
      StatsObserver::onorderbooksnapshotmessage (m);
#if 0
      dumpFirst (m, "onorderbooksnapshotmessage v14");
#endif
      if (verbose)
      {
         dumpIdent (m);
         
         if (m->getDlyHghPrc () != NULL)
            std::cerr << " dlyHghPrc=" << *m->getDlyHghPrc ();
         if (m->getDlyLowPrc () != NULL)
            std::cerr << " dlyLowPrc=" << *m->getDlyLowPrc ();
         if (m->getTotTrdQty () != NULL)
            std::cerr << " totTrdQty=" << *m->getTotTrdQty ();
#if 0
         if (m->getCntrStatus () != NULL)
            std::cerr << " cntrStatus=" << *m->getCntrStatus ();
#endif
         
         const Sequence<EEBS14::orderbooksnapshotmessage::channelSeqNos>& sns =
            m->getChannelSeqNos ();
         if (! sns.empty ())
         {
            std::cerr << " seqNos=";
            u32 i;
            for (i = 0; i < sns.size ()-1; i ++)
               std::cerr << sns [i].getConsolSeqNum () << ",";
            std::cerr << sns [i].getConsolSeqNum ();
         }

         const Sequence<EEBS14::orderbooksnapshotmessage::entries>& lvls =
            m->getEntries ();
         if (! lvls.empty ())
         {
            std::cerr << " lvl 1/" << lvls.size () << ":"
                      << " type=" << lvls [0].getEntryType ();
            if (lvls [0].getEntryPrcLvl () != NULL)
               std::cerr << " lvl=" << *lvls [0].getEntryPrcLvl ();
            std::cerr << " prc=" << lvls [0].getEntryPrc ()
                      << " qty=" << lvls [0].getEntryQty ();
            if (lvls [0].getEntryPrcSrc () != NULL)
               std::cerr << " src=" << *lvls [0].getEntryPrcSrc ();
         }
      }
      std::cerr << std::endl;
   }
   
   void onproductreferencemessage (
      const EEBS14::productreferencemessage::Ptr & m)
   {
      StatsObserver::onproductreferencemessage (m);
      dumpFirst (m, "onproductreferencemessage v14");
      if (verbose)
      {
         std::cerr << " seqNum=" << m->getSeqNum ()
                   << " actionType=" << m->getActionType ()
                   << " prodId=" << m->getProdId ()
                   << " prodType=" << m->getProdType ()
                   << " exchIdCode=" << m->getExchIdCode ()
                   << " isinCode=" << m->getIsinCode ()
                   << " currTypeCode=" << m->getCurrTypCode ()
                   << " noOfContracts=" << m->getNoOfContracts ()
                   << " implied=" << m->getImplied ();
         if (m->getExerciseStyle ())
            std::cerr << " exerciseStyle=" << * m->getExerciseStyle ();
         if (m->getUndrId ())
            std::cerr << " undrId=" << * m->getUndrId ();
         if (m->getUndrIsin ())
            std::cerr << " undrIsin=" << * m->getUndrIsin ();
         std::cerr << " ticSize=" << m->getTicSize ()
                   << " ticValue=" << m->getTicValue ();

         const Sequence<EEBS14::productreferencemessage::streams>& streams =
            m->getStreams ();
         for (u32 i = 0; i < streams.size (); i ++)
         {
            const EEBS14::productreferencemessage::streams& s = streams [i];
            std::cerr << " Stream:" << i+1
                      << " type=" << s.getStreamType ()
                      << " service=" << s.getStreamService ()
                      << " addr=" << s.getStreamAddr ()
                      << " port=" << s.getStreamPort ()
                      << " dpth=" << s.getMktDpth ();
         }
      }
      std::cerr << std::endl;
   }

#if 0
   void onproductstatusmessage (
      const EEBS14::productstatusmessage::Ptr & m)
   {
      StatsObserver::onproductstatusmessage (m);
      dumpFirst (m, "onproductstatusmessage v14");
      if (verbose)
         std::cerr << " prodId=" << m->getProdId ()
                   << " prodStatus=" << m->getProdStatus ();
      std::cerr << std::endl;
   }
#endif
      
   void onrequestmessage (
      const EEBS14::requestmessage::Ptr & m)
   {
      StatsObserver::onrequestmessage (m);
      dumpFirst (m, "onrequestmessage v14");
      if (verbose)
      {
         dumpIdent (m);
         std::cerr << " actionType=" << m->getActionType ()
                   << " reqType=" << m->getReqType ()
                   << " reqBidQty=" << m->getReqBidQty ()
                   << " reqAskQty=" << m->getReqAskQty ()
                   << " reqTim=" << m->getReqTim ();
      }
      std::cerr << std::endl;
   }
   
   void onsinglelegreferencemessage (
      const EEBS14::singlelegreferencemessage::Ptr & m)
   {
      StatsObserver::onsinglelegreferencemessage (m);
      std::cerr << "onsinglelegreferencemessage v14" << std::endl;
   }
   
   void onstartproductreferenceinformation (
      const EEBS14::startproductreferenceinformation::Ptr & m)
   {
      StatsObserver::onstartproductreferenceinformation (m);
      std::cerr << "onstartproductreferenceinformation v14" << std::endl;
   }
   
   void onstartservice (
      const EEBS14::startservice::Ptr & m)
   {
      StatsObserver::onstartservice (m);
      std::cerr << "onstartservice v14" << std::endl;
   }
   
   void onstartsinglelegreferenceinformation (
      const EEBS14::startsinglelegreferenceinformation::Ptr & m)
   {
      StatsObserver::onstartsinglelegreferenceinformation (m);
      std::cerr << "onstartsinglelegreferenceinformation v14";
      if (verbose)
      {
         std::cerr << " tsp=" << m->getTimestamp ()
                   << " mode=" << m->getMode ()
                   << " busDate=" << m->getBusDate ()
                   << " noOfMsgs=" << m->getNoOfMsgs ();
      }
      std::cerr << std::endl;
   }
   
   void onstartsinglelegsnapshotinformation (
      const EEBS14::startsinglelegsnapshotinformation::Ptr & m)
   {
      StatsObserver::onstartsinglelegsnapshotinformation (m);
      std::cerr << "onstartsinglelegsnapshotinformation v14";
      if (verbose)
      {
         std::cerr << " tsp=" << m->getTimestamp ();
         if (m->getProdId ())
            std::cerr << " prodId=" << *m->getProdId ();
         if (m->getNoOfMsgs ())
            std::cerr << " noOfMsgs=" << *m->getNoOfMsgs ();
      }
      std::cerr << std::endl;
   }
   
   void onstartstrategyreferenceinformation (
      const EEBS14::startstrategyreferenceinformation::Ptr & m)
   {
      StatsObserver::onstartstrategyreferenceinformation (m);
      std::cerr << "onstartstrategyreferenceinformation v14" << std::endl;
   }
   
   void onstartstrategysnapshotinformation (
      const EEBS14::startstrategysnapshotinformation::Ptr & m)
   {
      StatsObserver::onstartstrategysnapshotinformation (m);
      std::cerr << "onstartstrategysnapshotinformation v14" << std::endl;
   }
   
   void onstrategyreferencemessage (
      const EEBS14::strategyreferencemessage::Ptr & m)
   {
      StatsObserver::onstrategyreferencemessage (m);
      std::cerr << "onstrategyreferencemessage v14" << std::endl;
   }
   
   void ontrademessage (
      const EEBS14::trademessage::Ptr & m)
   {
      StatsObserver::ontrademessage (m);
      dumpFirst (m, "ontrademessage v14");

      if (verbose)
      {
         if (m->getGapIndicator () != NULL && * m->getGapIndicator () == "2")
            std::cerr << " GAP";
         
         dumpIdent (m);
#if 0         
         const Sequence<EEBS14::trademessage::entries>& lvls = m->getEntries ();
         std::cerr << " lvl 1/" << lvls.size () << ":"
                   << " tim=" << lvls [0].getEntryTim ()
                   << " type=" << lvls [0].getEntryType ()
                   << " prc=" << lvls [0].getEntryPrc ()
                   << " qty=" << lvls [0].getEntryQty ()
                   << " tpSeqNum=" << lvls [0].getTpSeqNum ();
#endif
      }
      std::cerr << std::endl;
   }

private:
   bool verbose;
};


static void usage ()
{
   std::cerr
      << "usage: eurexebsmd <ipmcdump|ipmcstats> <schema> <templates> <addr> <port> [<interface addr>]\n"
      << "       eurexebsmd tap <schema> <templates> <addr> <port> <localaddr> <outfile> [count]\n"
      << "       eurexebsmd <dump|stats> <schema> <templates> <input-fast-file>\n"
      << "       eurexebsmd <bufdump|bufstats> <schema> <templates> <input-fast-file>" << std::endl;
}

int
main (int argc, const char ** argv)
{
   std::ios::sync_with_stdio (false);

   try
   {
      FastDecoder dec;
      MarketDataClient mdc (dec);
      StatsObserver* observer = NULL;
      
      if (argc < 4)
      {
         usage ();
         exit (1);
      }
      
      const char* command = argv [1];
      const char* schema = argv [2];
      const char* templates = argv [3];
      
      if (strstr (command, "dump") != 0)
      {
         DumpObserver* obs = new DumpObserver (dec);
         observer = obs;
         if (strstr (command, "xdump") != 0)
            obs->setVerbose (true);
      }
      else
      {
         StatsObserver* obs = new StatsObserver (dec);
         observer = obs;
      }

      dec.addObserver (* observer);
      dec.loadSchema (schema);
      dec.loadTemplates (templates);
      dec.setLenient (true);

      Nanotime start = Nanotime::now ();

      if (strcmp (command, "tap") == 0)
      {
         if (argc < 8 || argc > 9)
         {
            usage ();
            exit (1);
         }
         
         if (argc == 8)
         {
            // MarketDataClient can join IP MC and output to file
            McTap::tap (argv [4], atoi (argv [5]), argv [6], argv [7]);
         }
         else
         {
            // MarketDataClient can join IP MC and output to file, terminating
            // the recording after the specified number of messages
            McTap::tap (argv [4], atoi (argv [5]), argv [6], argv [7],
                        atoi (argv [8]));
         }
      }
      else if (strstr (command, "ipmc") != NULL)
      {
         // MarketDataClient can also join an IP Multicast stream
         if (argc > 6)
            mdc.join (argv [4], atoi (argv [5]), argv [6]);
         else
            mdc.join (argv [4], atoi (argv [5]));
      }
      else if (strstr (command, "buf") != NULL)
      {
         // FastDecoder has a more raw interface that is demonstrated here
         int fd = ::open (argv [4], O_RDONLY);
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
         mdc.decode (argv [4]);

      Nanotime delta = Nanotime::now () - start;

      std::cout << observer->getMessageCount () << " messages processed in "
		<< delta.getMilli () << "ms (wall clock)" 
                << std::endl;
      if (mdc.getAggregatedDecodeTime ().isSet ())
        std::cout << "Aggregated decode time: "
                  << mdc.getAggregatedDecodeTime ().getMilli ()
                  << "ms" << std::endl;
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
