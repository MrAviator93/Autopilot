/***********************************************************************
FILE FLAGMODIFIER.HPP CONTAINS FLAG MODIFIER CLASS IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (15.05.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CORE_COMMON_FLAG_MODIFIER_HPP__
#define ATL_CORE_COMMON_FLAG_MODIFIER_HPP__

#include <bitset>
#include <ostream>
#include <type_traits>
#include <assert.h>

namespace ATL::Core::Common
{
//-----------------------------------------------------------------------
// FLAG MODIFIER
//
// Helper class to deal with flags (setting, unsetting, etc.)
//
// This object can be used in streamables, therefore set it's value
// via constructors!
//
// INT_TYPE - the type of the int that includes in itself the size of the ENUM
// ENUM_TYPE - the enumerator type for which we define the FlagModifier
//-----------------------------------------------------------------------

template < class INT_TYPE, class ENUM_TYPE >
class FlagModifier
{
	static_assert( std::is_integral_v< INT_TYPE >, "INT_TYPE must be an integral type." );

	static_assert( std::is_enum_v< ENUM_TYPE >, "ENUM_TYPE is not an enumerator." );

	static_assert( sizeof( INT_TYPE ) >= sizeof( ENUM_TYPE ),
				   "The size of INT_TYPE must be larger or equal to the size of ENUM_TYPE." );

	template < class I, class E >
	friend std::ostream& operator<<( std::ostream& out, const FlagModifier< I, E >& flagMod );

public:
	using IT = INT_TYPE;
	using ET = ENUM_TYPE;

	constexpr FlagModifier()
		: m_value { 0 }
	{ }

	explicit constexpr FlagModifier( INT_TYPE value );

	explicit constexpr FlagModifier( ENUM_TYPE e );

	template < class... Bits >
	explicit constexpr FlagModifier( Bits... bits );

	FlagModifier( const FlagModifier& ) = default;
	FlagModifier( FlagModifier&& ) = default;
	FlagModifier& operator=( const FlagModifier& ) = default;
	FlagModifier& operator=( FlagModifier&& ) = default;

	void constexpr setBits( ENUM_TYPE e );

	template < class... Bits >
	void constexpr setBits( ENUM_TYPE e, Bits... bits );

	void constexpr unsetBits( ENUM_TYPE e );

	template < class... Bits >
	void constexpr unsetBits( ENUM_TYPE e, Bits... bits );

	INT_TYPE getValue() const
	{
		return m_value;
	}

	explicit operator bool() const
	{
		return m_value;
	}

	bool isSet( ENUM_TYPE bit ) const;

	bool isNthBitSet( std::uint8_t bit ) const;

private:
	INT_TYPE m_value;
};

template < class I, class E >
std::ostream& operator<<( std::ostream& out, const FlagModifier< I, E >& flagMod )
{
	const auto bitCount = sizeof( I ) * 8;
	auto b = std::bitset< bitCount > { flagMod.getValue() };
	out << "0b" << b.to_string();
	return out;
}

template < class INT_TYPE, class ENUM_TYPE >
bool operator==( const FlagModifier< INT_TYPE, ENUM_TYPE >& a, const FlagModifier< INT_TYPE, ENUM_TYPE >& b )
{
	return a.getValue() == b.getValue();
}

template < class INT_TYPE, class ENUM_TYPE >
bool operator!=( const FlagModifier< INT_TYPE, ENUM_TYPE >& a, const FlagModifier< INT_TYPE, ENUM_TYPE >& b )
{
	return a.getValue() != b.getValue();
}

template < class INT_TYPE, class ENUM_TYPE >
inline constexpr FlagModifier< INT_TYPE, ENUM_TYPE >::FlagModifier( INT_TYPE value )
	: m_value { value }
{ }

template < class INT_TYPE, class ENUM_TYPE >
inline constexpr FlagModifier< INT_TYPE, ENUM_TYPE >::FlagModifier( ENUM_TYPE e )
	: m_value { static_cast< INT_TYPE >( e ) }
{ }

template < class INT_TYPE, class ENUM_TYPE >
template < class... Bits >
inline constexpr FlagModifier< INT_TYPE, ENUM_TYPE >::FlagModifier( Bits... bits )
{
	setBits( bits... );
}

template < class INT_TYPE, class ENUM_TYPE >
inline constexpr void FlagModifier< INT_TYPE, ENUM_TYPE >::setBits( ENUM_TYPE e )
{
	m_value |= static_cast< INT_TYPE >( e );
}

template < class INT_TYPE, class ENUM_TYPE >
template < class... Bits >
inline constexpr void FlagModifier< INT_TYPE, ENUM_TYPE >::setBits( ENUM_TYPE e, Bits... bits )
{
	setBits( e );
	setBits( bits... );
}

template < class INT_TYPE, class ENUM_TYPE >
inline constexpr void FlagModifier< INT_TYPE, ENUM_TYPE >::unsetBits( ENUM_TYPE e )
{
	m_value = m_value & ~static_cast< INT_TYPE >( e );
}

template < class INT_TYPE, class ENUM_TYPE >
template < class... Bits >
inline constexpr void FlagModifier< INT_TYPE, ENUM_TYPE >::unsetBits( ENUM_TYPE e, Bits... bits )
{
	unsetBits( e );
	unsetBits( bits... );
}

template < class INT_TYPE, class ENUM_TYPE >
inline bool FlagModifier< INT_TYPE, ENUM_TYPE >::isSet( ENUM_TYPE bit ) const
{
	return ( m_value & static_cast< INT_TYPE >( bit ) );
}

template < class INT_TYPE, class ENUM_TYPE >
inline bool FlagModifier< INT_TYPE, ENUM_TYPE >::isNthBitSet( std::uint8_t nthbit ) const
{
	if( nthbit <= ( sizeof( INT_TYPE ) * 8 ) )
	{
		return ( m_value & nthbit );
	}

	return false;
}

} // namespace ATL::Core::Common
#endif // ATL_CORE_COMMON_FLAG_MODIFIER_HPP__
