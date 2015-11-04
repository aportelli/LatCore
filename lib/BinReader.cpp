/*
 * BinReader.cpp, part of LatCore
 *
 * Copyright (C) 2015 Antonin Portelli
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

#include <LatCore/BinReader.hpp>
#include <LatCore/includes.hpp>

#if (defined __GNUC__)||(defined __clang__)
#pragma GCC diagnostic ignored "-Wunreachable-code"
#endif

using namespace std;
using namespace LatCore;

BinIO::BinIO(string msg, string loc)
: runtime_error("Binary reader error: " + msg + " (" + loc + ")")
{}

/******************************************************************************
 *                         BinReader implementation                           *
 ******************************************************************************/
// constructor /////////////////////////////////////////////////////////////////
BinReader::BinReader(const string fileName, const uint32_t endianness,
                     const bool isColMaj)
{
    open(fileName, endianness, isColMaj);
}

// I/O /////////////////////////////////////////////////////////////////////////
void BinReader::open(const string fileName, const uint32_t endianness,
                     const bool isColMaj)
{
    fileName_   = fileName;
    endianness_ = endianness;
    isColMaj_   = isColMaj;
    file_.reset(new ifstream(fileName_, ios::in|ios::binary|ios::ate));
    if (!file_->is_open())
    {
        IO_ERROR("impossible to open file '" + fileName_ + "'");
    }
    size_ = static_cast<size_t>(file_->tellg());
    file_->seekg(0, ios::beg);
}

void BinReader::close(void)
{
    file_.reset(nullptr);
}

template <>
std::string BinReader::read(void)
{
    std::string s;
    char        c = 'a';
    
    while (c != '\n')
    {
        c = read<char>();
        s.push_back(c);
    }
    
    return s;
}
