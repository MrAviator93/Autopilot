/***********************************************************************
FILE COMMONFUNCTIONS.HPP CONTAINS COMMON FUNCTIONS

FILE UTMOST REVIEW DONE ON (15.05.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CORE_BIT_UTILS_HPP__
#define ATL_CORE_BIT_UTILS_HPP__

#include <string>
#include <bitset>
#include <assert.h>
#include <exception>
#include <stdexcept>
#include <type_traits>

namespace ATL::Core::Common
{
template < typename INT_TYPE >
constexpr INT_TYPE bit( std::uint8_t shift ) noexcept( false )
{
	static_assert( std::is_integral_v< INT_TYPE >, "INT_TYPE must be an integral type." );

	if( shift == 0 )
	{
		return {};
	}

	if( shift > sizeof( INT_TYPE ) * 8 )
	{
		throw std::logic_error( "Bit shift can't be larger then the size of type in bits." );
	}

	INT_TYPE i { 1 };
	i <<= ( shift - 1 );
	return i;
}

template < typename INT_TYPE >
constexpr bool hasSinglebit( INT_TYPE value ) noexcept( true )
{
	static_assert( std::is_integral_v< INT_TYPE >, "INT_TYPE must be an integral type." );

	return ( value && !( value & ( value - 1 ) ) );
}

template < typename INT_TYPE >
constexpr bool isPowerOf2( INT_TYPE value )
{
	static_assert( std::is_integral_v< INT_TYPE >, "INT_TYPE must be an integral type." );

	return hasSinglebit< INT_TYPE >( value );
}

template < typename INT_TYPE >
constexpr INT_TYPE align( INT_TYPE val, INT_TYPE alignment )
{
	//static_cast( isPowerOf2<T>(alignment), "Alignment must be power of 2." );

	return ( val + ( alignment - 1 ) ) & ~( alignment - 1 );
}

template < typename UINT_TYPE >
constexpr UINT_TYPE findNearestPow2( UINT_TYPE value ) noexcept( true )
{
	static_assert( std::is_integral_v< UINT_TYPE >, "INT_TYPE must be an integral type." );

	static_assert( std::is_unsigned_v< UINT_TYPE >, "INT_TYPE must be an unsigned integral type." );

	if( value == 0 || value == 1 )
	{
		return { 2 };
	}

	if( isPowerOf2< UINT_TYPE >( value ) )
	{
		return value;
	}

	UINT_TYPE pow2Value { 1 };
	while( pow2Value < value )
	{
		pow2Value <<= 1;
	}

	return pow2Value;
}

template < typename UINT_TYPE >
constexpr std::string bitset( UINT_TYPE value ) noexcept( true )
{
	static_assert( std::is_integral_v< UINT_TYPE >, "INT_TYPE must be an integral type." );

	static_assert( std::is_unsigned_v< UINT_TYPE >, "INT_TYPE must be an unsigned integral type." );

	return { "0b" + std::bitset< sizeof( UINT_TYPE ) * 8 >( value ).to_string() };
}

} // namespace ATL::Core::Common
#endif // ATL_CORE_BIT_UTILS_HPP__
