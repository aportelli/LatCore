/*
 * Benchmark.hpp, part of LatCore
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

#ifndef LatCore_Benchmark_hpp_
#define LatCore_Benchmark_hpp_

#include <LatCore/LatCore.hpp>

BEGIN_LATCORE_NAMESPACE

/******************************************************************************
 *                           Benchmark class                                  *
 ******************************************************************************/

class Benchmark
{
public:
    // constructor
    Benchmark(void) = default;
    // destructor
    virtual ~Benchmark(void) = default;
    // set iteration
    void setKernel(const std::function<void(void)> &f);
    // set number of flops per iteration
    void setFlop(const unsigned long nFlop);
    // execute benchmark
    void run(const unsigned int n);
private:
    std::function<void(void)> kernel_{nullptr};
    double                    nFlop_{0};
};

END_LATCORE_NAMESPACE

#endif // LatCore_Benchmark_hpp_
