#include "BoundSphere.hpp"

#include <pugixml.hpp>

namespace ATL::Core::Math
{
BoundSphere::BoundSphere() noexcept( true )
	: x( 0.0f )
	, y( 0.0f )
	, z( 0.0f )
	, radius( 0.0f )
{ }

BoundSphere::BoundSphere( float radii ) noexcept( true )
	: x( 0.0f )
	, y( 0.0f )
	, z( 0.0f )
	, radius( radii )
{ }

BoundSphere::BoundSphere( float posX, float posY, float posZ, float bRadius ) noexcept( true )
	: x( posX )
	, y( posY )
	, z( posZ )
	, radius( bRadius )
{ }

BoundSphere::BoundSphere( const BoundSphere& bSphere ) noexcept( true )
	: x( bSphere.x )
	, y( bSphere.y )
	, z( bSphere.z )
	, radius( bSphere.radius )
{ }

BoundSphere::BoundSphere( const pugi::xml_node& boundSphereParentNode ) noexcept( true )
{
	parse( boundSphereParentNode );
}

void BoundSphere::serialize( pugi::xml_node& boundSphereParentNode )
{
	auto bSphereNode = boundSphereParentNode.append_child( BOUND_SPHERE_NODE_NAME );
	auto bCentroidNode = bSphereNode.append_child( "Centroid" );
	bCentroidNode.append_attribute( "x" ).set_value( x );
	bCentroidNode.append_attribute( "y" ).set_value( y );
	bCentroidNode.append_attribute( "z" ).set_value( z );
	bSphereNode.append_child( "Radius" ).append_attribute( "value" ).set_value( radius );
}

void BoundSphere::parse( const pugi::xml_node& boundSphereParentNode )
{
	parse( boundSphereParentNode, BOUND_SPHERE_NODE_NAME );
}

void BoundSphere::parse( const pugi::xml_node& boundSphereParentNode, const char* pBoundSphereNodeName )
{
	if( pBoundSphereNodeName )
	{
		const auto& bSphereNode = boundSphereParentNode.child( pBoundSphereNodeName );
		x = bSphereNode.child( "Centroid" ).attribute( "x" ).as_float();
		y = bSphereNode.child( "Centroid" ).attribute( "y" ).as_float();
		z = bSphereNode.child( "Centroid" ).attribute( "z" ).as_float();
		radius = bSphereNode.child( "Radius" ).attribute( "value" ).as_float();
	}
}

} // namespace ATL::Core::Math
