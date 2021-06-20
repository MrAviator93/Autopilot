/***********************************************************************
FILE SEMAPHORE.H CONTAINS SEMAPHORE IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (15.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_MULTITHREADING_SEMAPHORE_HPP__
#define ATL_CORE_MULTITHREADING_SEMAPHORE_HPP__

#include <mutex>
#include <condition_variable>

namespace ATL::Core::Multithreading
{
	//-----------------------------------------------------------------------
	// SEMAPHORE
	//
	// https://github.com/matus-chochlik/oglplus/blob/develop/example/advanced/cloud_trace/threads.hpp
	//-----------------------------------------------------------------------
	
	class CSemaphore
	{
	public:
		CSemaphore(size_t initial = 0);
		~CSemaphore() = default;

		void wait(std::size_t n = 1);
		void signal(std::size_t n = 1);
		bool signalled(std::size_t n = 1);

	private:
		std::size_t m_value;
		std::mutex m_mutex;
		std::condition_variable m_condVar;

		void decrement(void);
		void increment(std::size_t n);
	};

} // namespace ATL::Core::Multithreading
#endif // ATL_CORE_MULTITHREADING_SEMAPHORE_HPP__
