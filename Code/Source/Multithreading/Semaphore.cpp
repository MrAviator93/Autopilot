#include "Semaphore.hpp"

namespace ATL::Core::Multithreading
{
	CSemaphore::CSemaphore(size_t initial) : m_value(initial) {}

	void CSemaphore::wait(std::size_t n)
	{
		while (n--)
		{
			this->decrement();
		}
	}

	void CSemaphore::signal(std::size_t n)
	{
		this->increment(n);
	}

	bool CSemaphore::signalled(std::size_t n)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_value >= n;
	}

	void CSemaphore::decrement(void)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (m_value == 0)
		{
			m_condVar.wait(lock);
		}
		--m_value;
	}

	void CSemaphore::increment(std::size_t n)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_value += n;
		m_condVar.notify_all();
	}

} //namespace ATL::Core::Multithreading
