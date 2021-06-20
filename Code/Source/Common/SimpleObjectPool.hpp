/***********************************************************************
FILE SIMPLEOBJECTPOOL.H CONTAINS SIMPLE OBJECT POOL IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (06.06.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_COMMON_SIMPLE_OBJECT_POOL_HPP__
#define ATL_CORE_COMMON_SIMPLE_OBJECT_POOL_HPP__

#include "BitUtils.hpp"
#include "FlagModifier.hpp"

#include <NonCopyableMovable.hpp>

#include <assert.h>
#include <exception>
#include <type_traits>
#include <cstring>

namespace ATL::Core::Common
{
//-----------------------------------------------------------------------
// OBJECT FLAGS
//
// EO_IN_USE		- indicates that the allocated space is still in use
// EO_ARRAY			- indicates that the element is linked to an array ( not used yet ??? )
//-----------------------------------------------------------------------

enum ObjectFlags : std::uint32_t
{
	RESERVED_0 = bit< std::uint32_t >( 1 ),
	IN_USE = bit< std::uint32_t >( 2 ),
	ARRAY = bit< std::uint32_t >( 3 )
};

using ObjectFlagsMod = FlagModifier< std::uint32_t, ObjectFlags >; // ****** TODO: Put FlagModifier in use !

//-----------------------------------------------------------------------
// SIMPLE OBJECT POOL
//
// See implementation for details.
//-----------------------------------------------------------------------

template < class T >
class TSimpleObjectPool : Templates::CNonCopyableMovable
{
	// ****** TODO: Add some checks (check if a type has destructor, etc... )

	static_assert( std::is_destructible_v< T >, "Object must have destructor." );

public:
	TSimpleObjectPool( const std::uint32_t poolSize );
	~TSimpleObjectPool();

	T* allocateObject();
	template < class... Args >
	T* allocateObject( const Args&... args );

	// ****** TODO: To be implemented
	//T* allocateArray(const std::uint32_t count);
	//T* allocateArray(const std::uint32_t count, const Args& ... args);

	void destroyObject( T*& pObject );

private:
	std::uint32_t m_poolSize;
	std::uint32_t m_lastUsedIndex;
	ObjectFlagsMod* m_pFlagsArr;
	T* m_pObjectArr;
};

//-----------------------------------------------------------------------
// FUNCTION IMPLEMENTATIONS
//-----------------------------------------------------------------------

template < class T >
inline TSimpleObjectPool< T >::TSimpleObjectPool( const std::uint32_t poolSize )
	: m_poolSize { poolSize }
	, m_lastUsedIndex { 0 }
	, m_pFlagsArr { new ObjectFlagsMod[ poolSize ] }
{
	// Nullify flags
	memset( m_pFlagsArr, 0x00, sizeof( std::uint32_t ) * poolSize );

	// Allocate one large block of memory
	// that will hold all the object data
	m_pObjectArr = static_cast< T* >( malloc( sizeof( T ) * poolSize ) );
}

template < class T >
inline TSimpleObjectPool< T >::~TSimpleObjectPool()
{
	// Call destructor's!
	for( std::uint32_t i = 0; i < m_poolSize; i++ )
	{
		if( m_pFlagsArr[ m_lastUsedIndex ].isSet( ObjectFlags::IN_USE ) )
		{
			//m_pObjectArr[i].~T();
		}
	}

	// Do not forget to clean-up after ourselves
	delete[] m_pFlagsArr;
	free( m_pObjectArr );
}

template < class T >
inline T* TSimpleObjectPool< T >::allocateObject()
{
	if( !m_pFlagsArr[ m_lastUsedIndex ].isSet( ObjectFlags::IN_USE ) )
	{
		// Flag that the object space is in use
		m_pFlagsArr[ m_lastUsedIndex ].setBits( ObjectFlags::IN_USE );

		//memset(&m_pObjectArr[m_lastUsedIndex], 0x00, sizeof(T));

		return ( new( reinterpret_cast< void* >( &m_pObjectArr[ m_lastUsedIndex ] ) ) T );
	}

	for( std::uint32_t i = 0; i < m_poolSize; i++ )
	{
		if( !m_pFlagsArr[ i ].isSet( ObjectFlags::IN_USE ) )
		{
			// Flag that the object space is in use
			m_pFlagsArr[ i ].setBits( ObjectFlags::IN_USE );

			//memset(&m_pObjectArr[i], 0x00, sizeof(T));

			return ( new( reinterpret_cast< void* >( &m_pObjectArr[ i ] ) ) T );
		}
	}

	// ****** TODO: throw an error exception, we run out of bounds thats dangerous !

	// So it does not go out of bounds.
	return &m_pObjectArr[ m_poolSize - 1 ];
}

template < class T >
template < class... Args >
inline T* TSimpleObjectPool< T >::allocateObject( const Args&... args )
{
	if( !m_pFlagsArr[ m_lastUsedIndex ].isSet( ObjectFlags::IN_USE ) )
	{
		// Flag that the object space is in use
		m_pFlagsArr[ m_lastUsedIndex ].setBits( ObjectFlags::IN_USE );

		return ( new( reinterpret_cast< void* >( &m_pObjectArr[ m_lastUsedIndex ] ) ) T( args... ) );
	}

	for( std::uint32_t i = 0; i < m_poolSize; i++ )
	{
		if( !m_pFlagsArr[ i ].isSet( ObjectFlags::IN_USE ) )
		{
			// Flag that the object space is in use
			m_pFlagsArr[ i ].setBits( ObjectFlags::IN_USE );

			return ( new( reinterpret_cast< void* >( &m_pObjectArr[ i ] ) ) T( args... ) );
		}
	}

	// So it does not go out of bounds.
	return &m_pObjectArr[ m_poolSize - 1 ];
}

template < class T >
inline void TSimpleObjectPool< T >::destroyObject( T*& pObject )
{
	// Find the location in the array where the object lives
	std::uint32_t index = static_cast< std::uint32_t >( pObject - m_pObjectArr );

	// Check if index is inside the pool size (belongs to
	// allocated memory region)
	if( m_poolSize > index )
	{
		// Explicitly call destructor
		pObject->~T();

		memset( pObject, 0x00, sizeof( T ) );

		// Remove usage flag
		m_pFlagsArr[ index ].unsetBits( ObjectFlags::IN_USE );

		m_lastUsedIndex = index;

		pObject = nullptr;
	}
}

} // namespace ATL::Core::Common
#endif // ATL_CORE_COMMON_SIMPLE_OBJECT_POOL_HPP__
