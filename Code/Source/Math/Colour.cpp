#include "Colour.hpp"
#include <pugixml.hpp>

#include <cstring>
#include <algorithm>

namespace ATL::Core::Math
{
CColour::CColour()
{
	m_colour[ 0 ] = 0;
	m_colour[ 1 ] = 0;
	m_colour[ 2 ] = 0;
	m_colour[ 3 ] = 255;
}

CColour::CColour( std::uint8_t colour, std::uint8_t alpha ) noexcept( true )
{
	m_colour[ 0 ] = colour;
	m_colour[ 1 ] = colour;
	m_colour[ 2 ] = colour;
	m_colour[ 3 ] = alpha;
}

CColour::CColour( std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t alpha ) noexcept( true )
{
	m_colour[ 0 ] = r;
	m_colour[ 1 ] = g;
	m_colour[ 2 ] = b;
	m_colour[ 3 ] = alpha;
}

CColour::CColour( float colour, float alpha ) noexcept( true )
{
	alpha = std::clamp( alpha, 0.0f, 1.0f );

	if( colour >= 1.0f )
	{
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = 255;
		m_colour[ 3 ] = static_cast< std::uint8_t >( alpha * 255.0f );
		return;
	}

	if( colour <= 0.0f )
	{
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = 0;
		m_colour[ 3 ] = static_cast< std::uint8_t >( alpha * 255.0f );
		return;
	}

	m_colour[ 0 ] = static_cast< std::uint8_t >( colour * 255.0f );
	m_colour[ 1 ] = static_cast< std::uint8_t >( colour * 255.0f );
	m_colour[ 2 ] = static_cast< std::uint8_t >( colour * 255.0f );
	m_colour[ 3 ] = static_cast< std::uint8_t >( alpha * 255.0f );
}

CColour::CColour( float r, float g, float b, float alpha ) noexcept( true )
{
	m_colour[ 0 ] = static_cast< std::uint8_t >( r * 255.0f );
	m_colour[ 1 ] = static_cast< std::uint8_t >( g * 255.0f );
	m_colour[ 2 ] = static_cast< std::uint8_t >( b * 255.0f );
	m_colour[ 3 ] = static_cast< std::uint8_t >( alpha * 255.0f );
}

CColour::CColour( const ColourType colourType ) noexcept( true )
{
	switch( colourType )
	{
	case ColourType::BLACK: {
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = 0;
		m_colour[ 3 ] = 255;
		break;
	}
	case ColourType::WHITE: {
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = m_colour[ 3 ] = 255;
		break;
	}
	case ColourType::RED: {
		m_colour[ 0 ] = m_colour[ 3 ] = 255;
		m_colour[ 1 ] = m_colour[ 2 ] = 0;
		break;
	}
	case ColourType::BLUE: {
		m_colour[ 0 ] = m_colour[ 1 ] = 0;
		m_colour[ 2 ] = m_colour[ 3 ] = 255;
		break;
	}
	case ColourType::YELLOW: {
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 3 ] = 255;
		m_colour[ 2 ] = 0;
		break;
	}
	case ColourType::GREY: {
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 3 ] = 61;
		m_colour[ 3 ] = 255;
		break;
	}
	case ColourType::DARK_SLATE_GREY: {
		m_colour[ 0 ] = 47;
		m_colour[ 1 ] = m_colour[ 2 ] = 79;
		m_colour[ 3 ] = 255;
		break;
	}
	default:
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = 0;
		m_colour[ 3 ] = 255;
	}
}

CColour::CColour( const CColour& c ) noexcept( true )
{
	memcpy( m_colour, c.m_colour, sizeof( std::uint8_t ) * 4 );
}

CColour::CColour( CColour&& c ) noexcept( true )
{
	memcpy( m_colour, c.m_colour, sizeof( std::uint8_t ) * 4 );
}

CColour::CColour( const pugi::xml_node& colourBoxParentNode ) noexcept( true )
{
	parse( colourBoxParentNode );
}

bool CColour::operator==( const CColour& colour ) noexcept( true )
{
	if( m_colour[ 0 ] == colour.m_colour[ 0 ] && m_colour[ 1 ] == colour.m_colour[ 1 ] &&
		m_colour[ 2 ] == colour.m_colour[ 2 ] && m_colour[ 3 ] == colour.m_colour[ 3 ] )
	{
		return true;
	}
	return false;
}

void CColour::serialize( pugi::xml_node& colourBoxParentNode ) const
{
	auto colourNode = colourBoxParentNode.append_child( "Colour" );
	colourNode.append_attribute( "r" ).set_value( m_colour[ 0 ] );
	colourNode.append_attribute( "g" ).set_value( m_colour[ 1 ] );
	colourNode.append_attribute( "b" ).set_value( m_colour[ 2 ] );
	colourNode.append_attribute( "a" ).set_value( m_colour[ 3 ] );
}

void CColour::parse( const pugi::xml_node& colourBoxParentNode )
{
	auto colourNode = colourBoxParentNode.child( "Colour" );
	m_colour[ 0 ] = static_cast< std::uint8_t >( colourNode.attribute( "r" ).as_uint() );
	m_colour[ 1 ] = static_cast< std::uint8_t >( colourNode.attribute( "g" ).as_uint() );
	m_colour[ 2 ] = static_cast< std::uint8_t >( colourNode.attribute( "b" ).as_uint() );
	m_colour[ 3 ] = static_cast< std::uint8_t >( colourNode.attribute( "a" ).as_uint() );
}

} // namespace ATL::Core::Math
