/***********************************************************************
FILE CTIMER.H CONTAINS TIMER CLASS IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (15.05.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_CORE_COMMON_CORE_TIMER_HPP__
#define ATL_CORE_COMMON_CORE_TIMER_HPP__

#include <chrono>

namespace ATL::Core::Common
{
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point< Clock >;

//-----------------------------------------------------------------------
// TIMER
//
// Based on high_resolution_clock clock.
//
// Important change: Time point used to be std::chrono::time_point< std::chrono::steady_clock >,
// but that's not correct, now it's changed to std::chrono::time_point< Clock >
//
// Conversion units:
// 1s = 1000ms 		(milli-seconds)
// 1s = 1000000us 	(micro-seconds)
// 1s = 1e+9ns		(nano-seconds)
//-----------------------------------------------------------------------

class CTimer
{
public:
	// Default Ctor
	// Automatically starts the timer when created.
	CTimer();

	// Explicit call to start the timer.
	void start();

	// Resets the timer ( calls start() internally )
	void reset();

	// Returns elapsed time in seconds.
	double getElapsedTimeS() const;

	// Returns elapsed time in milliseconds.
	std::int64_t getElapsedTimeMs() const;

	// Returns elapsed time in microseconds.
	std::int64_t getElapsedTimeUs() const;

	// Returns elapsed time in nanoseconds.
	std::int64_t getElapsedTimeNs() const;

private:
	Clock m_clock;
	TimePoint m_startTP;
};

} // namespace ATL::Core::Common
#endif // ATL_CORE_COMMON_CORE_TIMER_HPP__
