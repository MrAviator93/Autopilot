#include "FlagModifier.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include <type_traits>
#include <iostream>

enum E1 : std::uint32_t
{
	VAL_1 = 0x0001,
	VAL_2 = VAL_1 << 1,
	VAL_3 = VAL_2 << 1,
	VAL_4 = VAL_3 << 1
};

SCENARIO( "Pure enumerator case" )
{
	GIVEN( "A single pure enumerator" )
	{
		ATL::Core::Common::FlagModifier< std::uint32_t, E1 > mod {};
		mod.setBits( E1::VAL_1, E1::VAL_3 );
		CHECK( mod.getValue() == 5 );
	}
}

int main( int argc, char* argv[] )
{
	doctest::Context ctx;

	ctx.setOption( "abort-after", 1 ); // Default - stop after 5 failed asserts

	ctx.applyCommandLine( argc, argv ); // Applies command line argc & argv

	ctx.setOption( "no-breaks", true ); // Override - don't break in the debugger

	int rslt = ctx.run(); // Run the test casses

	// Query flags ( and --exit ) rely on this
	if( ctx.shouldExit() )
	{
		// Propagate the result of the test casses
		return rslt;
	}

	// Any other program execution code can be added here

	return rslt; // + any other execution code
}