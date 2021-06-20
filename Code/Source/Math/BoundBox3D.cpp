#include "BoundBox3D.hpp"

#include <pugixml.hpp>

namespace ATL::Core::Math
{
BoundBox::BoundBox() noexcept( true )
	: minX { 0.0f }
	, minY { 0.0f }
	, minZ { 0.0f }
	, maxX { 0.0f }
	, maxY { 0.0f }
	, maxZ { 0.0f }
{
	padding[ 0 ] = padding[ 1 ] = 0.0f;
}

BoundBox::BoundBox( float value ) noexcept( true )
	: minX( -value )
	, minY( -value )
	, minZ( -value )
	, maxX( value )
	, maxY( value )
	, maxZ( value )
{
	padding[ 0 ] = padding[ 1 ] = 0.0f;
}

BoundBox::BoundBox( float min, float max ) noexcept( true )
	: minX( min )
	, minY( min )
	, minZ( min )
	, maxX( max )
	, maxY( max )
	, maxZ( max )
{
	padding[ 0 ] = padding[ 1 ] = 0.0f;
}

BoundBox::BoundBox( float minX_, float minY_, float minZ_, float maxX_, float maxY_, float maxZ_ ) noexcept( true )
	: minX( minX_ )
	, minY( minY_ )
	, minZ( minZ_ )
	, maxX( maxX_ )
	, maxY( maxY_ )
	, maxZ( maxZ_ )
{
	padding[ 0 ] = padding[ 1 ] = 0.0f;
}

BoundBox::BoundBox( const BoundBox& bbox ) noexcept( true )
	: minX( bbox.minX )
	, minY( bbox.minY )
	, minZ( bbox.minZ )
	, maxX( bbox.maxX )
	, maxY( bbox.maxY )
	, maxZ( bbox.maxZ )
{
	padding[ 0 ] = padding[ 1 ] = 0.0f;
}

BoundBox::BoundBox( const pugi::xml_node& boundBoxParentNode ) noexcept( true )
{
	parse( boundBoxParentNode );
}

void BoundBox::serialize( pugi::xml_node& boundBoxParentNode )
{
	auto bBoxNode = boundBoxParentNode.append_child( BOUND_BOX_NODE_NAME );
	auto bMinNode = bBoxNode.append_child( "Min" );
	bMinNode.append_attribute( "x" ).set_value( minX );
	bMinNode.append_attribute( "y" ).set_value( minY );
	bMinNode.append_attribute( "z" ).set_value( minZ );

	auto bMaxNode = bBoxNode.append_child( "Max" );
	bMaxNode.append_attribute( "x" ).set_value( maxX );
	bMaxNode.append_attribute( "y" ).set_value( maxY );
	bMaxNode.append_attribute( "z" ).set_value( maxZ );
}

void BoundBox::parse( const pugi::xml_node& boundBoxParentNode )
{
	parse( boundBoxParentNode, BOUND_BOX_NODE_NAME );
}

void BoundBox::parse( const pugi::xml_node& boundBoxParentNode, const char* pBoundBoxNodeName )
{
	if( pBoundBoxNodeName )
	{
		const auto& bBoxNode = boundBoxParentNode.child( pBoundBoxNodeName );
		minX = bBoxNode.child( "Min" ).attribute( "x" ).as_float();
		minY = bBoxNode.child( "Min" ).attribute( "y" ).as_float();
		minZ = bBoxNode.child( "Min" ).attribute( "z" ).as_float();
		maxX = bBoxNode.child( "Max" ).attribute( "x" ).as_float();
		maxY = bBoxNode.child( "Max" ).attribute( "y" ).as_float();
		maxZ = bBoxNode.child( "Max" ).attribute( "z" ).as_float();
	}
}

} // namespace ATL::Core::Math
