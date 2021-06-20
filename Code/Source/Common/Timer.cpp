#include "Timer.hpp"

namespace ATL::Core::Common
{
using ss = std::chrono::seconds; // Signed integer type of at least 35 bits
using ms = std::chrono::milliseconds; // Signed integer type of at least 45 bits
using us = std::chrono::microseconds; // Signed integer type of at least 55 bits
using ns = std::chrono::nanoseconds; // Signed integer type of at least 64 bits

CTimer::CTimer()
	: m_startTP( m_clock.now() )
{ }

void CTimer::start()
{
	m_startTP = m_clock.now();
}

void CTimer::reset()
{
	start();
}

double CTimer::getElapsedTimeS() const
{
	double result = this->getElapsedTimeUs() / 1000000.0;
	return result;
}

std::int64_t CTimer::getElapsedTimeMs() const
{
	return std::chrono::duration_cast< ms >( m_clock.now() - m_startTP ).count();
}

std::int64_t CTimer::getElapsedTimeUs() const
{
	return std::chrono::duration_cast< us >( m_clock.now() - m_startTP ).count();
	//std::chrono::time_point_cast<std::chrono::microseconts>(m_endTP).time_since_epoch().count
}

std::int64_t CTimer::getElapsedTimeNs() const
{
	return std::chrono::duration_cast< ns >( m_clock.now() - m_startTP ).count();
}

} // namespace ATL::Core::Common
