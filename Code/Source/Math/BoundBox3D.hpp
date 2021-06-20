/***********************************************************************
FILE BOUNDBOX.H CONTAINS BOUNDING BOX IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (30.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_MATH_BOUND_BOX_HPP__
#define ATL_CORE_MATH_BOUND_BOX_HPP__

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
// BOUNDING BOX
//
// Bounding box, 32 byte structure (consists of 6 floats & 2 padding floats)
// 32 byte structure is required for memory alignment purposes.
//
// ****** TODO: Consider additional functionality (intersection, etc.)
//-----------------------------------------------------------------------

B_ATTRIBUTE_ALIGNED16 struct BoundBox
{
	BoundBox() noexcept;

	explicit B_FORCE_INLINE BoundBox( float value ) noexcept( true );

	explicit B_FORCE_INLINE BoundBox( float min, float max ) noexcept( true );

	explicit B_FORCE_INLINE
	BoundBox( float minX_, float minY_, float minZ_, float maxX_, float maxY_, float maxZ_ ) noexcept;

	// Copy constructor
	explicit B_FORCE_INLINE BoundBox( const BoundBox& bbox ) noexcept;

	explicit B_FORCE_INLINE BoundBox( const pugi::xml_node& boundBoxParentNode ) noexcept;

	~BoundBox() noexcept = default;

	void serialize( pugi::xml_node& boundBoxParentNode );

	void parse( const pugi::xml_node& boundBoxParentNode );

	void parse( const pugi::xml_node& boundBoxParentNode, const char* pBoundBoxNodeName );

	float minX;
	float minY;
	float minZ;

	float maxX;
	float maxY;
	float maxZ;

	float padding[ 2 ];

	inline const static char* BOUND_BOX_NODE_NAME { "BoundBox" };
};

static_assert( sizeof( BoundBox ) == 32, "BoundBox struct size doesn't match the requirements." );

} // namespace ATL::Core::Math
#endif // ATL_CORE_MATH_BOUND_BOX_HPP__
