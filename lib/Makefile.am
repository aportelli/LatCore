COM_CXXFLAGS = -Wall -Wconversion
if CXX_GNU
    COM_CXXFLAGS += -W -pedantic
else
if CXX_INTEL
    COM_CXXFLAGS +=
endif
endif

include eigen_files.mk

nobase_dist_pkginclude_HEADERS = $(eigen_files) XML/tinyxml2.hpp
noinst_LTLIBRARIES             = libxml.la
lib_LTLIBRARIES                = libLatCore.la

libxml_la_SOURCES  = \
    XML/tinyxml2.hpp \
    XML/tinyxml2.cpp
libxml_la_CXXFLAGS = $(COM_CXXFLAGS) -Wno-sign-conversion

libLatCore_la_SOURCES = \
    Benchmark.cpp       \
    BinReader.cpp       \
    LatCore.cpp         \
    includes.hpp        \
    XmlReader.cpp       \
    XmlReader.hpp
libLatCore_ladir = $(pkgincludedir)
libLatCore_la_HEADERS = \
    Benchmark.hpp       \
    BinReader.hpp       \
    LatCore.hpp         \
    XmlReader.hpp
libLatCore_la_CXXFLAGS = $(COM_CXXFLAGS)
libLatCore_la_LIBADD   = libxml.la

ACLOCAL_AMFLAGS = -I .buildutils/m4
