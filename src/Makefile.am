# This is an automake file for the src directory of the
# STAREmaster utility.

# Ed Hartnett 3/16/20

AM_CPPFLAGS = -I$(top_srcdir)/include

# Create a library for STARE sidecar functionality.
lib_LTLIBRARIES = libstaremaster.la
libstaremaster_la_SOURCES = SidecarFile.cpp GeoFile.cpp		\
Modis05L2GeoFile.cpp Modis09L2GeoFile.cpp Modis09GAGeoFile.cpp

# This is the command line utility to create STARE sidecar files for
# data files.
bin_PROGRAMS = createSidecarFile
LDADD = libstaremaster.la
createSidecarFile_SOURCES = createSidecarFile.cpp 

EXTRA_DIST = CMakeLists.txt


