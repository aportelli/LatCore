/*
 * XmlReader.cpp, part of LatCore
 *
 * Copyright (C) 2013 - 2014 Antonin Portelli
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

#include <XmlReader.hpp>

using namespace std;
using namespace LatCore;

XmlParsing::XmlParsing(string msg, string loc)
: runtime_error("XML reader error: " + msg + " (" + loc + ")")
{}

/******************************************************************************
 *                         XmlReader implementation                           *
 ******************************************************************************/
// constructor /////////////////////////////////////////////////////////////////
XmlReader::XmlReader(const string &fileName)
{
    open(fileName);
}

// IO //////////////////////////////////////////////////////////////////////////
void XmlReader::open(const string &fileName)
{
    name_ = fileName;
    doc_.LoadFile(name_.c_str());
    if (doc_.Error())
    {
        string errMsg1, errMsg2;
        
        if (doc_.GetErrorStr1())
        {
            errMsg1 = doc_.GetErrorStr1();
        }
        if (doc_.GetErrorStr2())
        {
            errMsg2 = doc_.GetErrorStr2();
        }
        XML_ERROR("cannot open file " + fileName + " [tinyxml2 code "
                  + strFrom(doc_.ErrorID()) + ": " + errMsg1 + " - "
                  + errMsg2 + "]");
    }
    root_ = doc_.RootElement();
}

// XML structure access ////////////////////////////////////////////////////////
const XmlNode * XmlReader::getNextNode(const XmlNode *node)
{
    if (node)
    {
        return node->NextSiblingElement();
    }
    else
    {
        return nullptr;
    }
}
