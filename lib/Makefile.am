COM_CXXFLAGS = -Wall
if CXX_GNU
    COM_CXXFLAGS += -W -pedantic -Wno-deprecated-declarations
else
if CXX_INTEL
    COM_CXXFLAGS += -wd1682
endif
endif

include eigen_files.mk

nobase_dist_pkginclude_HEADERS = $(eigen_files) XML/tinyxml2.hpp
lib_LTLIBRARIES                = libLatCore.la

libLatCore_la_SOURCES = \
    Benchmark.cpp       \
    BinReader.cpp       \
    LatCore.cpp         \
    includes.hpp        \
    OptParser.cpp       \
    XmlReader.cpp       \
    XmlReader.hpp       \
    XML/tinyxml2.hpp    \
    XML/tinyxml2.cpp
libLatCore_ladir = $(pkgincludedir)
libLatCore_la_HEADERS = \
    Benchmark.hpp       \
    BinReader.hpp       \
    EigenPlugin.hpp     \
    LatCore.hpp         \
    OptParser.hpp       \
    XmlReader.hpp
libLatCore_la_CXXFLAGS = $(COM_CXXFLAGS)

ACLOCAL_AMFLAGS = -I .buildutils/m4
