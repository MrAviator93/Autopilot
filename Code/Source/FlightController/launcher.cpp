#include <CTimer.hpp>

#include <date/date.h>
#include <fmt/format.h>
#include <boost/filesystem.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

// Note base namespace is atl
// everything for flight controller must
// go into the following namespace
// namespace atl::fc

using namespace atl;

int main( int argc, char* argv[] )
{
    CTimer t;
    t.start();
    
    fmt::print( "Starting Flight Controller ...\n" );

    fmt::print( "Time elapsed: {}\n", t.getElapsedTimeS() );

    return 0;
}

