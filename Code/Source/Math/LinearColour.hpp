/***********************************************************************
FILE LINEARCOLOUR.HPP CONTAINS LINEAR COLOR CLASS IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (30.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_MATH_CORE_MATH_LINEAR_COLOUR_HPP__
#define ATL_MATH_CORE_MATH_LINEAR_COLOUR_HPP__

#include "Colour.hpp"

namespace pugi
{
class xml_node;
} // namespace pugi

namespace ATL::Core::Math
{
//-----------------------------------------------------------------------
// LINEAR COLOUR
//
// Stores colour of 32 bits of precision per channel.
//-----------------------------------------------------------------------

class CLinearColour
{
public:
	CLinearColour() noexcept( true );

	// LinearColour input range [0.0f : 1.0f]
	explicit CLinearColour( float colour, float alpha = 1.0f ) noexcept( true );

	// LinearColour input range [0.0f : 1.0f]
	explicit CLinearColour( float r, float g, float b, float alpha = 1.0f ) noexcept( true );

	explicit CLinearColour( const CColour& colour ) noexcept( true );

	explicit CLinearColour( const CLinearColour& colour ) noexcept( true );

	explicit CLinearColour( const ColourType colourType ) noexcept( true );

	explicit CLinearColour( const pugi::xml_node& linColourBoxParentNode ) noexcept( true );

	~CLinearColour() = default;

	bool operator==( const CLinearColour& colour ) noexcept( true );

	void serialize( pugi::xml_node& linColourBoxParentNode ) const;

	void parse( const pugi::xml_node& linColourBoxParentNode );

	float r() const
	{
		return m_colour[ 0 ];
	}

	float g() const
	{
		return m_colour[ 1 ];
	}

	float b() const
	{
		return m_colour[ 2 ];
	}

	float a() const
	{
		return m_colour[ 3 ];
	}

private:
	float m_colour[ 4 ]; //r, g, b, a
};

static_assert( sizeof( CLinearColour ) == 16, "The size of Linear Colour class must be the size of 16 bytes." );

} // namespace ATL::Core::Math
#endif // ATL_MATH_CORE_MATH_LINEAR_COLOUR_HPP__
