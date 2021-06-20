#include "SpinLock.hpp"

#include <thread>

#if defined( ATL_PLATFORM_LINUX )
	#include <sched.h>
#endif

using namespace std;
using namespace std::chrono;

namespace ATL::Core::Multithreading
{
	void CMicroSpinLock::lock() noexcept
	{
		while (!cas(MSL::FREE, MSL::LOCKED))
		{
			do 
			{
				std::this_thread::sleep_for(std::chrono::microseconds(10));

			} while (payload()->load(std::memory_order_relaxed) == MSL::LOCKED);
		}
	}

	void CMicroSpinLock::unlock() noexcept
	{
		payload()->store(MSL::FREE, std::memory_order_release);
	}

	bool CSpinLock::isLocked()
	{
		if (*(volatile uint32_t*)&m_locked == 0)
		{
			if (!m_locked.test_and_set(std::memory_order_acquire))
			{
				return false;
			}
		}
		return true;
	}

	void CSpinLock2::lock()
	{
		const int MAX_SPIN = 1000;
		int count = 0;

		while (true)
		{
			if (!m_locked.load(std::memory_order_relaxed))
			{
				if (tryLock())
				{
					return;
				}
			}

			if (count < MAX_SPIN)
			{
				count++;
				//_mm_pause();
				//_sleep(0);
				std::this_thread::sleep_for( std::chrono::microseconds( 0 ) );
			}
			else
			{
				std::this_thread::sleep_for( std::chrono::microseconds( 10 ) );
			}
		}
	}

} //namespace ATL::Core::Multithreading
