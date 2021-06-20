#include "LinearColour.hpp"
#include <pugixml.hpp>

#include <algorithm>

namespace ATL::Core::Math
{
CLinearColour::CLinearColour() noexcept( true )
{
	m_colour[ 0 ] = 0.0f;
	m_colour[ 1 ] = 0.0f;
	m_colour[ 2 ] = 0.0f;
	m_colour[ 3 ] = 1.0f;
}

CLinearColour::CLinearColour( float colour, float alpha ) noexcept( true )
{
	colour = std::clamp( colour, 0.0f, 1.0f );
	alpha = std::clamp( alpha, 0.0f, 1.0f );
	m_colour[ 0 ] = colour;
	m_colour[ 1 ] = colour;
	m_colour[ 2 ] = colour;
	m_colour[ 3 ] = alpha;
}

CLinearColour::CLinearColour( float r, float g, float b, float alpha ) noexcept( true )
{
	r = std::clamp( r, 0.0f, 1.0f );
	g = std::clamp( r, 0.0f, 1.0f );
	b = std::clamp( r, 0.0f, 1.0f );
	alpha = std::clamp( r, 0.0f, 1.0f );
	m_colour[ 0 ] = r;
	m_colour[ 1 ] = g;
	m_colour[ 2 ] = b;
	m_colour[ 3 ] = alpha;
}

CLinearColour::CLinearColour( const CColour& colour ) noexcept( true )
{
	m_colour[ 0 ] = static_cast< float >( colour.r() ) / 255.0f;
	m_colour[ 1 ] = static_cast< float >( colour.r() ) / 255.0f;
	m_colour[ 2 ] = static_cast< float >( colour.r() ) / 255.0f;
	m_colour[ 3 ] = static_cast< float >( colour.r() ) / 255.0f;
}

CLinearColour::CLinearColour( const CLinearColour& colour ) noexcept( true )
{
	m_colour[ 0 ] = colour.r();
	m_colour[ 1 ] = colour.g();
	m_colour[ 2 ] = colour.b();
	m_colour[ 3 ] = colour.a();
}

CLinearColour::CLinearColour( const ColourType colourType ) noexcept( true )
{
	switch( colourType )
	{
	case ColourType::BLACK: {
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = 0;
		m_colour[ 3 ] = 1.0f;
		break;
	}
	case ColourType::WHITE: {
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = m_colour[ 3 ] = 1.0f;
		break;
	}
	case ColourType::RED: {
		m_colour[ 0 ] = m_colour[ 3 ] = 1.0f;
		m_colour[ 1 ] = m_colour[ 2 ] = 0;
		break;
	}
	case ColourType::BLUE: {
		m_colour[ 0 ] = m_colour[ 1 ] = 0;
		m_colour[ 2 ] = m_colour[ 3 ] = 1.0f;
		break;
	}
	case ColourType::YELLOW: {
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 3 ] = 1.0f;
		m_colour[ 2 ] = 0;
		break;
	}
	case ColourType::GREY: {
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = 0.24f;
		m_colour[ 3 ] = 1.0f;
		break;
	}
	case ColourType::DARK_SLATE_GREY: {
		m_colour[ 0 ] = 0.1843f;
		m_colour[ 1 ] = m_colour[ 2 ] = 0.3098f;
		m_colour[ 3 ] = 255;
		break;
	}
	default: // BLACK
		m_colour[ 0 ] = m_colour[ 1 ] = m_colour[ 2 ] = 0.0f;
		m_colour[ 3 ] = 1.0f;
	}
}

CLinearColour::CLinearColour( const pugi::xml_node& linColourBoxParentNode ) noexcept( true )
{
	parse( linColourBoxParentNode );
}

bool CLinearColour::operator==( const CLinearColour& colour ) noexcept( true )
{
	if( m_colour[ 0 ] == colour.m_colour[ 0 ] && m_colour[ 1 ] == colour.m_colour[ 1 ] &&
		m_colour[ 2 ] == colour.m_colour[ 2 ] && m_colour[ 3 ] == colour.m_colour[ 3 ] )
	{
		return true;
	}
	return false;
}

void CLinearColour::serialize( pugi::xml_node& linColourBoxParentNode ) const
{
	auto colourNode = linColourBoxParentNode.append_child( "LinearColour" );
	colourNode.append_attribute( "r" ).set_value( m_colour[ 0 ] );
	colourNode.append_attribute( "g" ).set_value( m_colour[ 1 ] );
	colourNode.append_attribute( "b" ).set_value( m_colour[ 2 ] );
	colourNode.append_attribute( "a" ).set_value( m_colour[ 3 ] );
}

void CLinearColour::parse( const pugi::xml_node& linColourBoxParentNode )
{
	auto colourNode = linColourBoxParentNode.child( "LinearColour" );
	m_colour[ 0 ] = colourNode.attribute( "r" ).as_float();
	m_colour[ 1 ] = colourNode.attribute( "g" ).as_float();
	m_colour[ 2 ] = colourNode.attribute( "b" ).as_float();
	m_colour[ 3 ] = colourNode.attribute( "a" ).as_float();
}

} // namespace ATL::Core::Math
