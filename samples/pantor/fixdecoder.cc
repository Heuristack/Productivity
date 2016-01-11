// Copyright (c), Pantor Engineering AB, 1999-2011
// All rights reserved

///////////////////////////////////////////////////////////////////////////
//
//   This program reads fix tag/value messages from a file
//
///////////////////////////////////////////////////////////////////////////

#include "presto/base/RuntimeEnv.h"
#include "presto/base/DataModel.h"
#include "base/app/CmdLine.h"
#include "presto/fix/TvDecoder.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#if ! defined (OS_win)
#include <unistd.h>
#endif


using namespace Pantor;
using namespace Presto;

// Command line specification

static const char * CmdLineSpec =
   "fixdecoder [-h/--help]                     # Display this help"
   "           [-L/--lib <dir-or-jar>...]      # Resource library path"
   "           -s/--schema <schema-file>...    # FMS Schema"
   "           [-v/--verbosity <level>]        # Verbosity level"
   "           [-t/--trace...]                 # Trace level"
   "           file...                         # File to decode"
   ;

struct MyObs : public Fix::TvDecoder::ErrorObserver
{
   MyObs (const DataModel & dm_) : dm (dm_) { }

   void onAny (const Dymo::ObjectSptr & obj)
   {
      dm.writeAsText (obj, std::cout);
   }

   void onError (const StrList & errors, const Dymo::ObjectSptr &,
                 const Dymo::GroupDef &)
   {
      std::cerr << "Decoding errors:" << std::endl;
      for (StrList::const_iterator i = errors.begin (), e = errors.end ();
           i != e; ++ i)
         std::cerr << "  " << *i << std::endl;
   }
   
   const DataModel & dm;
};

// The run function sets up the FIX client and initiates the processing

int
run (int argc, const char ** argv)
{
   CmdLine cl (argc, argv, CmdLineSpec);

   if (cl.printUsageOrValidate ())
      return EXIT_SUCCESS;

   // Set trace level
   
   RuntimeEnv::setLogOpt ("prestofix", "trace", cl.count ("trace"));
   
   // Setup the data model. The Presto::DataModel holds meta data
   // about available messages and their structure. The data model is
   // setup by loading FIX Message Schemas (FMS) in XML format.

   DataModel dm (cl.getList ("lib"));
   dm.loadSchemas (cl.getList ("schema"));

   // Create a decoder that uses the data model. Setup a simple observer that
   // will receive all decoded messages and any errors. The observer
   // will dump the decoded messages as text

   MyObs obs (dm);
   Fix::TvDecoder decoder (dm);
   decoder.setErrorObserver (obs);
   decoder.setMethod (&MyObs::onAny, obs);

   // Decode the input files
   
   StrList files = cl.getList ("file");

   for (StrList::const_iterator i = files.begin (), e = files.end (); i != e;
        ++ i)
   {
      int fd = ::open (i->c_str (), O_RDONLY);
      if (fd < 0)
         throw RuntimeException (std::string (strerror (errno)) + ": " + *i);
            
      u8 buf [8192];
         
      for (;;)
      {
         u32 n = ::read (fd, (char*) buf, sizeof (buf));
         decoder.decode (buf, n);
         if (n < sizeof (buf))
            break;
      }
   }

   // Check that the input was complete
   
   decoder.checkCompleteness ();
   
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
