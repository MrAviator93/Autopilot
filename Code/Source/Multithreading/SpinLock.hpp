/***********************************************************************
FILE SPINLOCK.H CONTAINS SPINLOCK IMPLEMENTATION

http://www.gamedev.ru/code/forum/?id=198628
http://en.cppreference.com/w/cpp/atomic/atomic_flag

FILE UTMOST REVIEW DONE ON (15.05.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CORE_MULTITHREADING_SPINLOCK_HPP__
#define ATL_CORE_MULTITHREADING_SPINLOCK_HPP__

#include <atomic>
#include <type_traits>

#pragma warning (disable : 4996)

typedef unsigned int uint32;

namespace ATL::Core::Multithreading 
{

	//-----------------------------------------------------------------------
	// MICRO SPIN LOCK GUARD
	//
	// Do not forget to call init() method for the micro-spin-lock before usage!
	//-----------------------------------------------------------------------

	template< class SPIN_LOCK_TYPE >
	class TMicroSpinLockGuard
	{
	public:
		TMicroSpinLockGuard( SPIN_LOCK_TYPE& lock ) : m_spinLock{ lock } 
		{
			m_spinLock.lock();
		}

		~TMicroSpinLockGuard()
		{
			m_spinLock.unlock();
		}

		TMicroSpinLockGuard(const TMicroSpinLockGuard< SPIN_LOCK_TYPE >&) = delete;
		TMicroSpinLockGuard& operator=(const TMicroSpinLockGuard< SPIN_LOCK_TYPE >&) = delete;

		TMicroSpinLockGuard( TMicroSpinLockGuard< SPIN_LOCK_TYPE >&&) = delete;
		TMicroSpinLockGuard& operator=( TMicroSpinLockGuard< SPIN_LOCK_TYPE >&&) = delete;

	private:
		SPIN_LOCK_TYPE & m_spinLock;
	};

	//-----------------------------------------------------------------------
	// TEMPLATE SPIN LOCK GUARD CLASS
	//-----------------------------------------------------------------------

	template< class SPIN_LOCK_TYPE >
	class TSpinLockGuard
	{
	public:
		TSpinLockGuard( SPIN_LOCK_TYPE & lock) : m_spinLock{ lock }
		{
			m_spinLock.lock();
		}

		~TSpinLockGuard()
		{
			m_spinLock.unlock();
		}

		TSpinLockGuard(const TSpinLockGuard< SPIN_LOCK_TYPE >&) = delete;
		TSpinLockGuard& operator=(const TSpinLockGuard< SPIN_LOCK_TYPE >&) = delete;

		TSpinLockGuard(TSpinLockGuard< SPIN_LOCK_TYPE >&&) = delete;
		TSpinLockGuard& operator=(TSpinLockGuard< SPIN_LOCK_TYPE >&&) = delete;

	private:
		SPIN_LOCK_TYPE& m_spinLock;
	};

	//-----------------------------------------------------------------------
	// MICRO SPIN LOCK
	//
	// POD type spinlock (so it can be used in other packed type objects).
	//-----------------------------------------------------------------------

	class CMicroSpinLock
	{
		enum MSL { FREE = 0, LOCKED = 1 };
	public:

		void init()
		{
			payload()->store(MSL::FREE);
		}

		bool tryLock() noexcept
		{
			bool ret = cas(MSL::FREE, MSL::LOCKED);
			return ret;
		}

		void lock() noexcept;

		void unlock() noexcept;

	private:
		std::atomic< uint32 >* payload() noexcept 
		{
			return reinterpret_cast<std::atomic<uint32>*>(&this->m_lock);
		}

		bool cas(uint32 compare, uint32 newVal) noexcept
		{
			return std::atomic_compare_exchange_strong_explicit(
				payload(),
				&compare,
				newVal,
				std::memory_order_acquire,
				std::memory_order_relaxed);
		}

		uint32 m_lock;
	};

	static_assert(std::is_pod<CMicroSpinLock>::value, "CMicroSpinLock must be kept a POD type.");

	//-----------------------------------------------------------------------
	// SPIN LOCK
	//
	// Advanced spin-lock implementation, spins for 1000 iterations and then
	// puts the thread to sleep for 0 seconds.
	//
	// Based on std::atomic_flag
	//-----------------------------------------------------------------------

	class CSpinLock 
	{
	public:
		CSpinLock() = default;
		~CSpinLock() = default;

		CSpinLock( const CSpinLock& ) = delete;
		CSpinLock& operator=( const CSpinLock& ) = delete;
		CSpinLock( CSpinLock&& ) = delete;
		CSpinLock& operator=( CSpinLock&& ) = delete;

		void lock();
		void unlock() { m_locked.clear(std::memory_order_release); }
		bool isLocked();

	private:
		std::atomic_flag m_locked = ATOMIC_FLAG_INIT;
	};

	//-----------------------------------------------------------------------
	// SPIN LOCK 2
	//
	// Advanced spin-lock implementation, spins for 1000 iterations and then
	// puts the thread to sleep for 0 seconds.
	//
	// Based on std::atomic_bool
	//-----------------------------------------------------------------------

	class CSpinLock2
	{
	public:
		CSpinLock2() { this->unlock(); }
		~CSpinLock2() = default;

		CSpinLock2( const CSpinLock2& ) = delete;
		CSpinLock2& operator=( const CSpinLock2& ) = delete;
		CSpinLock2( CSpinLock2&& ) = delete;
		CSpinLock2& operator=( CSpinLock2&& ) = delete;
		
		void lock();

		bool tryLock()
		{
			return !m_locked.exchange(true, std::memory_order_acquire);
		}

		void unlock()
		{
			m_locked.store(false, std::memory_order_release);
		}

		bool isLocked() const { return m_locked.load(); }

	private:
		std::atomic_bool m_locked;
	};

	template< typename T >
	constexpr bool isMicroSpinlock()
	{
	    if constexpr( std::is_same_v< CMicroSpinLock, T > )
	    {
		return true;
	    }

	    return false;
	}


} // namespace ATL::Core::Multithreading
#endif // ATL_CORE_MULTITHREADING_SPINLOCK_HPP__
