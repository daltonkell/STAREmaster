/// @file
/// This class contains the main functionality for reading a file for
/// which STARE sidecar files may be constructed.

// Ed Hartnett 4/4/20

/**
 * @mainpage
 *
 * @section intro Introduction
 *
 * The STAREmaster utility computes STARE indicies for common NASA
 * datasets.
 *
 * STAREmaster consists of:
 * - a command line utility to create STARE sidecar files
 * - a C++ library to read geo-location information from selected data sets.
 *
 * STAREmaster also uses the STARE library, which computes the
 * spacio-temporal indicies for the geo-location data that STAREmaster
 * reads from the data file.
 * 
 * @section createSidecarFile Command Line Tool createSidecarFile
 *
 * The command line tool creates a sidecar file for a scienfic data
 * set.
 *
 * Use the command line tool like this:
 *
 * createSidecarFile -d dataset_code data_file
 *
 * The full set of options is listed with --help:
 * <pre>
STARE spatial create sidecar file. 
Usage: ./createSidecarFile [options] [filename]} 
Examples:
  ./createSidecarFile data.nc
  ./createSidecarFile data.h5

Options:
   -h, --help        : print this help
   -v, --verbose     : verbose: print all
   -q, --quiet       : don't chat, just give back index
   -b, --build_level : Higher levels -> longer initialization time. (default is 5)
   -d, --data_type   : Allows specification of data type.
   -o, --output_file : Provide file name for output file.
   -r, --output_dir  : Provide output directory name.
</pre>
 *
 * @section STAREmasterLibrary STAREmaster Library
 *
 * The STAREmaster library is a C++ library which can read targeted
 * data sets and determine their geo-location information.
 *
 * Each data set which is understood by the STAREmaster library has a class file with full documentation.
 *
 * Data Set | Library Class
 * ---------|--------------
 * MOD05    | ModisL2GeoFile
 * MOD09    | Modis09L2GeoFile
 * 
 * @section refs References
 * 
 * MODIS HDF4 Level 2 Documentation: Ocean Level-2 Data Products,
 * March 22, 2010
 * https://oceancolor.gsfc.nasa.gov/docs/format/Ocean_Level-2_Data_Products.pdf
 *
 * MODIS netCDF Level 2 Documentation: Ocean Level-2 Data Format
 * Specification, https://oceancolor.gsfc.nasa.gov/docs/format/l2nc/
 *
 */
#include "config.h"
#include "GeoFile.h"
#include <mfhdf.h>
#include <hdf.h>
#include <HdfEosDef.h>

/**
 * Determine the format of the target file.
 *
 * @param fileName Name of the target file.
 * @param gf_format Pointer to int that gets a constant indicating the
 * format. Ignored if NULL.
 *
 * @return 0 for success, error code otherwise.
 */
int
GeoFile::determineFormat(const std::string fileName, int *gf_format)
{
    int32 swathfileid;
    
    if (gf_format)
	*gf_format = SSC_FORMAT_HDF4;

    // Try to open as swath file with the HDF-EOS library.
    swathfileid = SWopen(fileName.c_str(), DFACC_RDONLY);
    if (swathfileid != -1)
    {
	if (gf_format)
	    *gf_format = SSC_FORMAT_MODIS_L2;	

	// Close the swath file.
	if (SWclose(swathfileid) < 0)
	    return SSC_EHDF4ERR;
    }
    
    return 0;
}

