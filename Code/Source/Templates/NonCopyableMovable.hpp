/***********************************************************************
FILE NONCOPYABLE.H CONTAINS NON COPYABLE INTERFACE

FILE UTMOST REVIEW DONE ON (15.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_TEMPLATES_NON_COPYABLE_MOVABLE_HPP__
#define ATL_CORE_TEMPLATES_NON_COPYABLE_MOVABLE_HPP__

namespace ATL::Core::Templates
{
//-----------------------------------------------------------------------
// NON-COPYABLE-MOVABLE
//
// Non-copyable idiom
// Inherit this class as private to make child class non-copyable and non-movable.
//-----------------------------------------------------------------------

class CNonCopyableMovable
{
protected:
	CNonCopyableMovable() = default;
	~CNonCopyableMovable() = default;

	CNonCopyableMovable( const CNonCopyableMovable& ) = delete; // Prevent construction by copying
	CNonCopyableMovable& operator=( const CNonCopyableMovable& ) = delete; // Prevent assignment

	CNonCopyableMovable( CNonCopyableMovable&& ) = delete; // Prevent construction by move
	CNonCopyableMovable& operator=( CNonCopyableMovable&& ) = delete; // Prevent move assignment
};

} // namespace ATL::Core::Templates
#endif // ATL_CORE_TEMPLATES_NON_COPYABLE_MOVABLE_HPP__
