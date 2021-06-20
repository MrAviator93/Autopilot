/***********************************************************************
FILE FENCE.H CONTAINS FENCE IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (15.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_MULTITHREADING_FENCE_HPP__
#define ATL_CORE_MULTITHREADING_FENCE_HPP__

#include "SpinLock.hpp"

#include <NonCopyableMovable.hpp>
#include <condition_variable>

namespace ATL::Core::Multithreading
{
	using CondVarAny = std::condition_variable_any;

	//-----------------------------------------------------------------------
	// FENCE
	//
	// Use when one thread needs to wait for another thread to execute some task,
	// create a CFence object, pass it as one of arguments into other's methods parameters
	// and use method fence.wait().
	//
	// fence.wait() blocks the thread that created the fence until notification methods are called
	//
	// At the end of other's threaded methods execution it is necessary to call either:
	// fence.notifyOne() to notify only one waiting thread
	// fence.notifyAll() to notify all waiting threads
	//-----------------------------------------------------------------------

	class CFence : Templates::CNonCopyableMovable
	{
	public:
		CFence();
		~CFence();

		// Blocks the thread (using Spin lock internally)
		// that created the fence until notification methods are called.
		void wait();

		// When other threads call notifyX() method, the spinlock is released
		// and the waiting thread may proceed further.
		void notifyOne();
		void notifyAll();

	private:
		CSpinLock2 m_spinLock;
		CondVarAny m_condVar;
	};

} // namespace ATL::Core::Multithreading
#endif // ATL_CORE_MULTITHREADING_FENCE_HPP__
