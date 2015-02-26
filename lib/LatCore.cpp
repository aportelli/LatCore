/*
 * LatCore.cpp, part of LatCore
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

#include <LatCore/LatCore.hpp>
#include <LatCore/includes.hpp>

using namespace std;
using namespace LatCore;

void LatCore::testFunction(void)
{}

ostream & LatCore::operator<<(ostream &out, const ProgressBar &&bar)
{
    const Index nTick = bar.nCol_*bar.current_/bar.total_;
    
    out << "[";
    for (Index i = 0; i < nTick; ++i)
    {
        out << "=";
    }
    for (Index i = nTick; i < bar.nCol_; ++i)
    {
        out << " ";
    }
    out << "] " << bar.current_ << "/" << bar.total_;
    out.flush();
    
    return out;
}
