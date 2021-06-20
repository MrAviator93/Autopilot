/***********************************************************************
FILE COLOUR.H CONTAINS COLOUR DECLARATIONS

FILE UTMOST REVIEW DONE ON (30.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_MATH_COLOUR_HPP__
#define ATL_CORE_MATH_COLOUR_HPP__

#include <cstdint>

namespace pugi
{
class xml_node;
} // namespace pugi

namespace ATL::Core::Math
{
//-----------------------------------------------------------------------
// COLOUR TYPE
//
// Defines all primitive colour types.
//-----------------------------------------------------------------------

enum class ColourType
{
	BLACK,
	WHITE,
	RED,
	BLUE,
	YELLOW,
	GREY,
	DARK_SLATE_GREY
};

//-----------------------------------------------------------------------
// COLOUR CLASS
//
// Stores colour of 8 bits of precision per channel.
//-----------------------------------------------------------------------

class CColour
{
public:
	CColour();

	// Input range [0 : 255]
	explicit CColour( std::uint8_t colour, std::uint8_t alpha = 255 ) noexcept( true );

	explicit CColour( std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t alpha = 255 ) noexcept( true );

	// Colour input range [0.0f : 1.0f]
	explicit CColour( float colour, float alpha = 1.0f ) noexcept( true );

	// Colour input range [0.0f : 1.0f]
	explicit CColour( float r, float g, float b, float alpha = 1.0f ) noexcept( true );

	explicit CColour( const ColourType colourType ) noexcept( true );

	explicit CColour( const CColour& c ) noexcept( true );

	explicit CColour( CColour&& c ) noexcept( true );

	explicit CColour( const pugi::xml_node& colourBoxParentNode ) noexcept( true );

	~CColour() = default;

	bool operator==( const CColour& colour ) noexcept;

	void serialize( pugi::xml_node& colourBoxParentNode ) const;

	void parse( const pugi::xml_node& colourBoxParentNode );

	std::uint8_t r() const
	{
		return m_colour[ 0 ];
	}

	std::uint8_t g() const
	{
		return m_colour[ 1 ];
	}

	std::uint8_t b() const
	{
		return m_colour[ 2 ];
	}

	std::uint8_t a() const
	{
		return m_colour[ 3 ];
	}

	std::uint8_t* rgba()
	{
		return m_colour;
	}

private:
	std::uint8_t m_colour[ 4 ]; // r, g, b, a
};

static_assert( sizeof( CColour ) == 4, "The size of Colour class must be 4 bytes." );

} // namespace ATL::Core::Math
#endif // ATL_CORE_MATH_COLOUR_HPP__
