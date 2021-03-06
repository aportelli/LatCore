/*
 * LatCore.hpp, part of LatCore
 *
 * Copyright (C) 2013 - 2015 Antonin Portelli
 *
 * LatCore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LatCore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LatCore.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LatCore_Global_hpp_
#define	LatCore_Global_hpp_

#include <algorithm>
#include <array>
#include <chrono>
#include <complex>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

// Eigen inclusion
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MATRIXBASE_PLUGIN <LatCore/EigenPlugin.hpp>
#include <LatCore/Eigen/Dense>

// namespace definition
#define BEGIN_LATCORE_NAMESPACE namespace LatCore {
#define END_LATCORE_NAMESPACE }

// macro utilities
#define unique_arg(...) __VA_ARGS__
#define DEBUG_VAR(x) std::cout << #x << "= "  << x << std::endl
#define DEBUG_MAT(m) std::cout << #m << "=\n" << m << std::endl

// attribute to switch off unused warnings with gcc
#ifdef __GNUC__
#define __dumb __attribute__((unused))
#else
#define __dumb
#endif

// max length for paths
#define MAX_PATH_LENGTH 512u

// copy/assignement from Eigen expression
#define EIGEN_EXPR_CTOR(ctorName, Class, Base, ExprType) \
template <typename Derived>\
ctorName(const ExprType<Derived> &m): Base(m) {}\
template<typename Derived>\
Class & operator=(const ExprType<Derived> &m)\
{\
    this->Base::operator=(m);\
    return *this;\
}

// source location
#define LATCORE_SRC_LOC strFrom(__FUNCTION__) + " at " + strFrom(__FILE__)\
                        + ":" + strFrom(__LINE__)

BEGIN_LATCORE_NAMESPACE

// Eigen type aliases //////////////////////////////////////////////////////////
const int dynamic = Eigen::Dynamic;

// array types
template <typename Derived>
using ArrayExpr = Eigen::ArrayBase<Derived>;

template <typename T, int nRow = dynamic, int nCol = dynamic>
using Array = Eigen::Array<T, nRow, nCol>;

// matrix types
template <typename Derived>
using MatExpr = Eigen::MatrixBase<Derived>;

template <typename T, int nRow = dynamic, int nCol = dynamic>
using MatBase = Eigen::Matrix<T, nRow, nCol>;

template <int nRow, int nCol>
using SFMat = Eigen::Matrix<float, nRow, nCol>;

template <int nRow, int nCol>
using SDMat = Eigen::Matrix<double, nRow, nCol>;

template <int nRow, int nCol>
using SCMat = Eigen::Matrix<std::complex<double>, nRow, nCol>;

// vector types
template <typename T, int size = dynamic>
using Vec = MatBase<T, size, 1>;

template <int size>
using SIVec = Vec<int, size>;

template <int size>
using SUVec = Vec<unsigned int, size>;

template <int size>
using SFVec = Vec<float, size>;

template <int size>
using SDVec = Vec<double, size>;

template <int size>
using SCVec = Vec<std::complex<double>, size>;

typedef SIVec<dynamic> IVec;
typedef SUVec<dynamic> UVec;
typedef SDVec<dynamic> DVec;
typedef SCVec<dynamic> CVec;

// block types
template <typename Derived>
using Block      = Eigen::Block<Derived>;
template <typename Derived>
using ConstBlock = const Eigen::Block<const Derived>;

template <typename Derived>
using Row      = typename Derived::RowXpr;
template <typename Derived>
using ConstRow = typename Derived::ConstRowXpr;

template <typename Derived>
using Col = typename Derived::ColXpr;
template <typename Derived>
using ConstCol = typename Derived::ConstColXpr;

// map type
template <int stride>
using InnerStride = Eigen::InnerStride<stride>;
template <int rowStride, int colStride>
using Stride = Eigen::Stride<rowStride, colStride>;
template <typename Derived, typename StrideType = Stride<0, 0>>
using Map = Eigen::Map<Derived, Eigen::Unaligned, StrideType>;
template <typename Derived, typename StrideType = Stride<0, 0>>
using ConstMap = Eigen::Map<const Derived, Eigen::Unaligned, StrideType>;

// Index type //////////////////////////////////////////////////////////////////
typedef MatBase<int>::Index Index;

#define FOR_VEC(vec, i)  for (LatCore::Index i = 0; i < (vec).size(); ++i)
#define FOR_ARRAY(ar, i) FOR_VEC(ar, i)

// Random seed type ////////////////////////////////////////////////////////////
typedef std::random_device::result_type SeedType;

// Type utilities //////////////////////////////////////////////////////////////
// pointer type test
template <typename Derived, typename Base>
inline bool isDerivedFrom(const Base *pt)
{
    return (dynamic_cast<const Derived *>(pt) != nullptr);
}

// static logical or
template <bool... b>
struct static_or;

template <bool... tail>
struct static_or<true, tail...> : static_or<tail...> {};

template <bool... tail>
struct static_or<false, tail...> : std::false_type {};

template <>
struct static_or<> : std::true_type {};

// Environment /////////////////////////////////////////////////////////////////
void testFunction(void);

// String utilities ////////////////////////////////////////////////////////////
inline std::string extension(const std::string fileName)
{
    return fileName.substr(fileName.find_last_of(".") + 1);
}

template <typename T>
inline T strTo(const std::string &str)
{
    T buf;
    std::istringstream stream(str);
    
    stream >> buf;
    
    return buf;
}

// optimized specializations
template <>
inline float strTo<float>(const std::string &str)
{
    return strtof(str.c_str(), (char **)NULL);
}
template <>
inline double strTo<double>(const std::string &str)
{
    return strtod(str.c_str(), (char **)NULL);
}
template <>
inline int strTo<int>(const std::string &str)
{
    return (int)(strtol(str.c_str(), (char **)NULL, 10));
}
template <>
inline long strTo<long>(const std::string &str)
{
    return strtol(str.c_str(), (char **)NULL, 10);
}
template <>
inline std::string strTo<std::string>(const std::string &str)
{
    return str;
}

template <typename T>
inline std::string strFrom(const T x)
{
    std::ostringstream stream;
    
    stream << x;
    
    return stream.str();
}

// specialization for vectors
template<>
inline DVec strTo<DVec>(const std::string &str)
{
    DVec                res;
    std::vector<double> vbuf;
    double              buf;
    std::istringstream  stream(str);
    
    while (!stream.eof())
    {
        stream >> buf;
        vbuf.push_back(buf);
    }
    res = Map<DVec>(vbuf.data(), static_cast<Index>(vbuf.size()));
    
    return res;
}

template<>
inline IVec strTo<IVec>(const std::string &str)
{
    IVec                res;
    std::vector<int>    vbuf;
    int                 buf;
    std::istringstream  stream(str);
    
    while (!stream.eof())
    {
        stream >> buf;
        vbuf.push_back(buf);
    }
    res = Map<IVec>(vbuf.data(), static_cast<Index>(vbuf.size()));
    
    return res;
}

template<>
inline UVec strTo<UVec>(const std::string &str)
{
    UVec                      res;
    std::vector<unsigned int> vbuf;
    unsigned int              buf;
    std::istringstream        stream(str);

    while (!stream.eof())
    {
        stream >> buf;
        vbuf.push_back(buf);
    }
    res = Map<UVec>(vbuf.data(), static_cast<Index>(vbuf.size()));

    return res;
}

template <typename T>
void tokenReplace(std::string &str, const std::string token,
                  const T &x, const std::string mark = "@")
{
    std::string fullToken = mark + token + mark;
    
    auto pos = str.find(fullToken);
    if (pos != std::string::npos)
    {
        str.replace(pos, fullToken.size(), strFrom(x));
    }
}

// Manifest file reader ////////////////////////////////////////////////////////
inline std::vector<std::string> readManifest(const std::string manFileName)
{
    std::vector<std::string> list;
    std::ifstream            manFile;
    char                     buf[MAX_PATH_LENGTH];
    
    manFile.open(manFileName);
    while (!manFile.eof())
    {
        manFile.getline(buf, MAX_PATH_LENGTH);
        if (!std::string(buf).empty())
        {
            list.push_back(buf);
        }
    }
    manFile.close();
    
    return list;
}

// Recursive directory creation ////////////////////////////////////////////////
int mkdir(const std::string dirName);

// C++ version of basename /////////////////////////////////////////////////////
std::string basename(const std::string& s);

// Progress bar class //////////////////////////////////////////////////////////
class ProgressBar
{
public:
    // constructor
    template <typename A, typename B>
    ProgressBar(const A current, const B total, const Index nCol = 60);
    // IO
    friend std::ostream & operator<<(std::ostream &out,
                                     const ProgressBar &&bar);
private:
    Index current_, total_, nCol_;
};

template <typename A, typename B>
ProgressBar::ProgressBar(const A current, const B total, const Index nCol)
: current_(static_cast<Index>(current))
, total_(static_cast<Index>(total))
, nCol_(nCol)
{}

std::ostream & operator<<(std::ostream &out, const ProgressBar &&bar);

// named variable interface ////////////////////////////////////////////////////
// FIXME: check redundant names and variable number limit
class VarName
{
public:
    // constructor
    VarName(const std::string defName);
    // destructor
    virtual ~VarName(void) = default;
    // access
    std::string getName(const Index i) const;
    void        setName(const Index i, const std::string name);
    // test
    bool hasName(const Index i) const;
private:
    std::string                            defName_;
    std::unordered_map<Index, std::string> name_;
};

END_LATCORE_NAMESPACE

#endif // LatCore_Global_hpp_
