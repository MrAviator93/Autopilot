/***********************************************************************
FILE BOUNDSPHERE.H CONTAINS BOUNDING SPHERE IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (09.02.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_MATH_CORE_MATH_BOUND_SPHERE_HPP__
#define ATL_MATH_CORE_MATH_BOUND_SPHERE_HPP__

#include <assert.h>

namespace pugi
{
class xml_node;
} // namespace pugi

namespace ATL::Core::Math
{
#define B_ATTRIBUTE_ALIGNED16
#define B_FORCE_INLINE

//-----------------------------------------------------------------------
// BOUNDING SPHERE
//
// Bounding sphere, 16 byte structure (consists of 4 floats)
//
// ****** TODO: Consider additional functionality (intersection, etc.)
//-----------------------------------------------------------------------

B_ATTRIBUTE_ALIGNED16 struct BoundSphere
{
	BoundSphere() noexcept;

	explicit B_FORCE_INLINE BoundSphere( float radii ) noexcept( true );

	explicit B_FORCE_INLINE BoundSphere( float posX, float posY, float posZ, float bRadius ) noexcept( true );

	// Copy constructor
	explicit B_FORCE_INLINE BoundSphere( const BoundSphere& bSphere ) noexcept( true );

	explicit B_FORCE_INLINE BoundSphere( const pugi::xml_node& boundSphereParentNode ) noexcept( true );

	~BoundSphere() = default;

	void serialize( pugi::xml_node& pBoundSphereParentNode );

	void parse( const pugi::xml_node& pBoundSphereParentNode );

	void parse( const pugi::xml_node& pBoundSphereParentNode, const char* pBoundSphereNodeName );

	// Centroid
	float x;
	float y;
	float z;
	float radius;

	inline const static char* BOUND_SPHERE_NODE_NAME { "BoundSphere" };
};

static_assert( sizeof( BoundSphere ) == 16, "BoundSphere struct size doesn't match the requirements." );

} // namespace ATL::Core::Math
#endif // ATL_MATH_CORE_MATH_BOUND_SPHERE_HPP__
