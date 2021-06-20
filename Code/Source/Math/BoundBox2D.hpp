/***********************************************************************
FILE BOUNDBOX2D.H CONTAINS BOUNDING BOX 2D IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (30.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_MATH_BOUND_BOX_2D_HPP__
#define ATL_CORE_MATH_BOUND_BOX_2D_HPP__

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
// BOUND BOX 2D
//
// User in user interface.
//-----------------------------------------------------------------------

B_ATTRIBUTE_ALIGNED16 struct BoundBox2D
{
	B_FORCE_INLINE BoundBox2D() noexcept( true );

	explicit B_FORCE_INLINE BoundBox2D( float value ) noexcept( true );

	// Copy constructor
	explicit B_FORCE_INLINE BoundBox2D( const BoundBox2D& bbox ) noexcept( true );

	~BoundBox2D() = default;

	void serialize( pugi::xml_node& boundBoxParentNode );

	void parse( const pugi::xml_node& boundBoxParentNode );

	void parse( const pugi::xml_node& boundBoxParentNode, const char* pBoundBoxNodeName );

	float minX;
	float minY;
	float maxX;
	float maxY;

	inline const static char* BOUND_BOX_2D_NODE_NAME { "BoundBox2D" };
};

static_assert( sizeof( BoundBox2D ) == 4 * sizeof( float ), "BoundBox2D struct size doesn't match the requirements." );

} // namespace ATL::Core::Math
#endif // ATL_CORE_MATH_BOUND_BOX_2D_HPP__
