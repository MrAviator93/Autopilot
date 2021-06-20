/***********************************************************************
FILE SINGLETON.H CONTAINS SINGLETON TEMPLATE

FILE UTMOST REVIEW DONE ON (25.01.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_TEMPLATES_SINGLETON_HPP__
#define ATL_CORE_TEMPLATES_SINGLETON_HPP__

#include "NonCopyableMovable.hpp"

namespace ATL::Core::Templates
{
//-----------------------------------------------------------------------
// SINGLETON TEMPLATE
//
// Usage: class CMySngleInstClass : public TSingleton<CMySingleInstClass> { ... };
// CMySingeInstClass::getInstance().mySpecialMethod();
//-----------------------------------------------------------------------

template < class T >
class TSingleton : private CNonCopyableMovable
{
public:
	static T& getInstance()
	{
		static T singleInstance;
		return singleInstance;
	}

private:
	TSingleton< T >() = default; // Prevent construction
	~TSingleton< T >() = default; // Prevent unwanted destruction
};

} // namespace ATL::Core::Templates
#endif // ATL_CORE_TEMPLATES_SINGLETON_HPP__
