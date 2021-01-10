#include "CTimer.hpp"

namespace atl
{
	using ss = std::chrono::seconds;
	using ms = std::chrono::milliseconds;
	using us = std::chrono::microseconds;
	using ns = std::chrono::nanoseconds;

	CTimer::CTimer() : m_startTP( m_clock.now() ) 
	{
		m_endTP = m_startTP;
	}

	double CTimer::getElapsedTimeS()
	{
		double result = this->getElapsedTimeUs() / 1000000.0;
		return result;	
	}

	int64 CTimer::getElapsedTimeMs()
	{
		m_endTP = m_clock.now();
		return std::chrono::duration_cast<ms>(m_endTP - m_startTP).count();
	}

	int64 CTimer::getElapsedTimeUs()
	{
		m_endTP = m_clock.now();
		return std::chrono::duration_cast<us>(m_endTP - m_startTP).count();
	}

	int64 CTimer::getElapsedTimeNs()
	{
		m_endTP = m_clock.now();
		return std::chrono::duration_cast<ns>(m_endTP - m_startTP).count();
	}

} // namespace atl