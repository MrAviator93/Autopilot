#include "BoundBox2D.hpp"

#include <pugixml.hpp>

namespace ATL::Core::Math
{
BoundBox2D::BoundBox2D() noexcept( true )
	: minX { 0.0f }
	, minY { 0.0f }
	, maxX { 0.0f }
	, maxY { 0.0f }
{ }

BoundBox2D::BoundBox2D( float value ) noexcept( true )
	: minX { value }
	, minY { value }
	, maxX { value }
	, maxY { value }
{ }

BoundBox2D::BoundBox2D( const BoundBox2D& bbox ) noexcept( true )
{
	minX = bbox.minX;
	minY = bbox.minY;
	maxX = bbox.maxX;
	maxY = bbox.maxY;
}

void BoundBox2D::serialize( pugi::xml_node& boundBoxParentNode )
{
	auto bBoxNode = boundBoxParentNode.append_child( BOUND_BOX_2D_NODE_NAME );
	auto bMinNode = bBoxNode.append_child( "Min" );
	bMinNode.append_attribute( "x" ).set_value( minX );
	bMinNode.append_attribute( "y" ).set_value( minY );

	auto bMaxNode = bBoxNode.append_child( "Max" );
	bMaxNode.append_attribute( "x" ).set_value( maxX );
	bMaxNode.append_attribute( "y" ).set_value( maxY );
}

void BoundBox2D::parse( const pugi::xml_node& boundBoxParentNode )
{
	parse( boundBoxParentNode, BOUND_BOX_2D_NODE_NAME );
}

void BoundBox2D::parse( const pugi::xml_node& boundBoxParentNode, const char* pBoundBoxNodeName )
{
	if( pBoundBoxNodeName )
	{
		const auto& bBoxNode = boundBoxParentNode.child( pBoundBoxNodeName );
		minX = bBoxNode.child( "Min" ).attribute( "x" ).as_float();
		minY = bBoxNode.child( "Min" ).attribute( "y" ).as_float();
		maxX = bBoxNode.child( "Max" ).attribute( "x" ).as_float();
		maxY = bBoxNode.child( "Max" ).attribute( "y" ).as_float();
	}
}

} // namespace ATL::Core::Math
