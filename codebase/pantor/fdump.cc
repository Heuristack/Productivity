// Copyright (c), Pantor Engineering AB, 1999-2011
// All rights reserved

#include "presto/base/RuntimeEnv.h"
#include "presto/base/DataModel.h"
#include "presto/base/Writer.h"
#include "presto/fast/FastDecoder.h"
#include "base/app/CmdLine.h"
#include <cerrno>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

using namespace Pantor;
using namespace Presto;

static const char * CmdLineSpec =
   "fdump [-h/--help]                       # Display this help"
   "      -t/--templates <template-file>... # FAST templates"
   "      [-s/--schema <schema-file>...]    # Data model schema. If no "
   "                                        #   schema is specified, "
   "                                        #   the templates will be used "
   "                                        #   as schemas"
   "      [-L/--lib <dir-or-jar>...]        # Resource library path"
   "      [-m/--method <output-method>]     # Output method: text, xml, tag, "
   "                                        #   json, bson"
   "      [-o/--output <file>]              # Output file"
   "      [-c/--compat-mode <cmode>]        # Compatibility mode"
   "      [-S/--stats]                      # Display decoding statistics"
   "      [-p/--packets]                    # Preserve packet boundaries"
   "                                        #   Each packet must be preceded"
   "                                        #   by a four byte, little endian"
   "                                        #   length preamble"
   "      [input]                           # FAST data file, defaults to"
   "                                        #   standard input"
   ;


void
decodeStream (FastDecoder & dec, int fd)
{
   u8 buf [8192];
         
   for (;;)
   {
      u32 n = ::read (fd, (char*) buf, sizeof (buf));
      dec.decode (buf, n);
      if (n < sizeof (buf))
         break;
   }
}

void
decodePackets (FastDecoder & dec, int fd)
{
   u32 bufSize = 8192;
   u8 * buf = new u8 [bufSize];
         
   for (;;)
   {
      union { u32 size; char bytes [sizeof (u32)]; } preamble;
      u32 n = ::read (fd, preamble.bytes, sizeof (u32));
      if (n < sizeof (u32))
         break;

      if (bufSize < preamble.size)
      {
         bufSize = preamble.size;
         delete [] buf;
         buf = new u8 [bufSize];
      }
      
      n = ::read (fd, (char*) buf, preamble.size);
      if (n < preamble.size)
         break;

      dec.decode (buf, n);
   }
}

int
run (int argc, const char ** argv)
{
   CmdLine cl (argc, argv, CmdLineSpec, CmdLine::UseLogOpts);

   if (cl.printUsageOrValidate ())
      return EXIT_SUCCESS;

   DataModel dm (cl.getList ("lib"));
   StrList schemas;
   if (cl.has ("schema"))
      schemas = cl.getList ("schema");
   else
      schemas = cl.getList ("templates");

   dm.loadSchemas (schemas);

   FastDecoder dec (dm, cl.get ("compat-mode"));
   dec.loadTemplates (cl.getList ("templates"));
   
   std::string method = "text";
   cl.get ("method", method);

   std::ostream * os;
   std::auto_ptr <std::ofstream> ofs;
   if (cl.has ("output"))
   {
      ofs.reset (new std::ofstream (cl.get ("output").c_str ()));
      os = ofs.get ();
   }
   else
      os = & std::cout;
   
   std::auto_ptr <Writer> wr (Writer::createWriter (method, dm, *os));
   dec.addObserverRegistry (wr->getObserverRegistry ());
   
   int fd;

   if (cl.has ("input"))
   {
      fd = ::open (cl.get ("input").c_str (), O_RDONLY);
      if (fd < 0)
         throw RuntimeException ("Cannot open " + cl.get ("input") + ": " +
                                 std::string (::strerror (errno)));
   }
   else
      fd = 0;

   
   Nanotime t1 (Nanotime::now ());
   
   if (cl.has ("packets"))
      decodePackets (dec, fd);
   else
      decodeStream (dec, fd);
   
   if (cl.has ("stats"))
   {
      Nanotime t2 (Nanotime::now ());
      u32 count = dec.getMsgCount ();
      u64 decTime = dec.getDecodeTime ();
      
      std::cerr << "Messages Count: " << count << std::endl;
      std::cerr << "Time:           "
                << (t2.getNano () - t1.getNano ()) / 1000000
                << " ms [Decode: " << decTime / 1000000 << " ms]"
                << std::endl;
   
      double secs = ((t2.getNano () - t1.getNano ()) / 1000000000.0);
      double decSecs = decTime / 1000000000.0;
      double mps = count / secs;
      double decMps = count / decSecs;
      std::cerr << "Rate:           " << std::fixed
                << std::setprecision (1) << mps << " msg/s [Decode: "
                << decMps << " msg/s]" << std::endl;
   }
   
   return EXIT_SUCCESS;
}

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
