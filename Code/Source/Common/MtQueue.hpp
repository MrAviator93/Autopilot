/***********************************************************************
FILE MTQUEUE.HPP CONTAINS MULTI THREAD SAFE QUEUE IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (16.05.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CORE_COMMON_MT_QUEUE_HPP__
#define ATL_CORE_COMMON_MT_QUEUE_HPP__

#include <NonCopyableMovable.hpp>

#include <list>
#include <mutex>
#include <vector>

namespace ATL::Core::Common
{
//-----------------------------------------------------------------------
// MULTI THREAD SAFE QUEUE
//
// A wrapper class around std::list, enabling thread safety and implementing
// methods simulating the queue.
//-----------------------------------------------------------------------

template < typename T >
class CMtQueue : Templates::CNonCopyableMovable
{
public:
	CMtQueue()
		: m_mutex {}
		, m_queue {}
	{ }
	~CMtQueue() = default;

	std::size_t size() const noexcept( true )
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		return m_queue.size();
	}

	bool empty() const noexcept( true )
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		return m_queue.empty();
	}

	void clear()
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		m_queue.clear();
	}

	void push( const T& element )
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		m_queue.push_back( element );
	}

	void push( T&& element )
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		m_queue.emplace_back( element );
	}

	// Picks and removes from the queue the first item and returns it.
	T get() // Rename to pop
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		T out = std::move( m_queue.front() );
		m_queue.pop_front();
		return out;
	}

	// Picks and removes from the queue n items and returns them packed into a vector.
	std::vector< T > get( std::size_t n )
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		if( m_queue.size() < n )
		{
			n = m_queue.size();
		}

		std::vector< T > out {};
		out.reserve( n );
		for( auto i = 0u; i < n; i++ )
		{
			out.emplace_back( std::move( m_queue.front() ) );
			m_queue.pop_front();
		}

		return out;
	}

	T peek_front()
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		return m_queue.front();
	}

	const T& peek_front() const
	{
		std::unique_lock< std::mutex > lock { m_mutex };
		return m_queue.front();
	}

private:
	mutable std::mutex m_mutex;
	std::list< T > m_queue;
};

} // namespace ATL::Core::Common
#endif // ATL_CORE_COMMON_MT_QUEUE_HPP__
