#include "CTimer.hpp"

namespace atl
{
	using ss = std::chrono::seconds;		// Signed integer type of at least 35 bits 
	using ms = std::chrono::milliseconds;	// Signed integer type of at least 45 bits
	using us = std::chrono::microseconds;	// Signed integer type of at least 55 bits
	using ns = std::chrono::nanoseconds;	// Signed integer type of at least 64 bits

	CTimer::CTimer() : m_startTP{ m_clock.now() }
	{
		m_endTP = m_startTP;
	}

	double CTimer::getElapsedTimeS()
	{
		double result = static_cast< double >( getElapsedTimeUs() ) / 1000000.0;
		return result;	
	}

	int64 CTimer::getElapsedTimeMs()
	{
		m_endTP = m_clock.now();
		return std::chrono::duration_cast< ms >( m_endTP - m_startTP ).count();
	}

	int64 CTimer::getElapsedTimeUs()
	{
		m_endTP = m_clock.now();
		return std::chrono::duration_cast< us >( m_endTP - m_startTP ).count();
	}

	int64 CTimer::getElapsedTimeNs()
	{
		m_endTP = m_clock.now();
		return std::chrono::duration_cast< ns >( m_endTP - m_startTP ).count();
	}

} // namespace atl