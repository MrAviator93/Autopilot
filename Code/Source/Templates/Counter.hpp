/***********************************************************************
FILE COUNTER.HPP CONTAINS COUNTER CLASS IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (15.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_TEMPLATES_COUNTER_HPP__
#define ATL_CORE_TEMPLATES_COUNTER_HPP__

#include <atomic>
#include <cstdint>

namespace ATL::Core::Templates
{
//-----------------------------------------------------------------------
// COUNTER
//
// Counts how many classes of type T we have.
// This class must be inherited either as private or protected.
// Use when it's necessary to keep track of class object count.
//-----------------------------------------------------------------------

template < class T >
class CCounter
{
public:
	CCounter()
	{
		m_counter++;
	}

	CCounter( const CCounter& c )
	{
		m_counter++;
	}

	CCounter& operator=( const CCounter& c )
	{
		if( this != &c )
		{
			m_counter++;
		}
		return *this;
	}

	CCounter( CCounter&& c )
	{
		m_counter++;
	}

	CCounter& operator=( CCounter&& c )
	{
		if( this != &c )
		{
			m_counter++;
		}
		return *this;
	}

	~CCounter()
	{
		m_counter--;
	}

	std::uint32_t operator()() const
	{
		return m_counter;
	}

	static std::uint32_t count()
	{
		return m_counter;
	}

private:
	inline static std::atomic_uint32_t m_counter {};
};

} // namespace ATL::Core::Templates
#endif // ATL_CORE_TEMPLATES_COUNTER_HPP__
