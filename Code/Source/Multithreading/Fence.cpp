#include "Fence.hpp"

namespace ATL::Core::Multithreading
{

	CFence::CFence()
	{
		m_spinLock.lock();
	}

	CFence::~CFence()
	{
		m_spinLock.unlock();
		//notifyAll();
		notifyOne();
	}

	void CFence::wait()
	{
		if ( m_spinLock.isLocked() )
		{
			m_condVar.wait( m_spinLock );
		}
	}

	void CFence::notifyOne()
	{
		m_spinLock.unlock();
		m_condVar.notify_one();
	}

	void CFence::notifyAll()
	{
		m_spinLock.unlock();
		m_condVar.notify_all();
	}

} // namespace ATL::Core::Multithreading
