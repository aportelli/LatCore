/*
 * Benchmark.cpp, part of LatCore
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

#include <LatCore/Benchmark.hpp>
#include <LatCore/includes.hpp>

using namespace std;
using namespace chrono;
using namespace LatCore;

/******************************************************************************
 *                         Benchmark implementation                           *
 ******************************************************************************/
// set iteration
void Benchmark::setKernel(const std::function<void(void)> &f)
{
    kernel_ = f;
}
// set number of flops per iteration
void Benchmark::setFlop(const unsigned long nFlop)
{
    nFlop_ = static_cast<double>(nFlop);
}

// get seconds since epoch /////////////////////////////////////////////////////
void Benchmark::run(const unsigned int n)
{
    time_point<high_resolution_clock> start, end;
    duration<double>                  t;

    start = high_resolution_clock::now();
    for (unsigned int i = 0; i < n; ++i)
    {
        kernel_();
    }
    end = high_resolution_clock::now();
    t   = end - start;
    cout << "Benchmark results: " << nFlop_*n << " flop -- ";
    cout << t.count() << " s -- ";
    cout << nFlop_*n/t.count() << " flop/s" << endl;
}
