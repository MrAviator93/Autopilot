/***********************************************************************
FILE CONTROLLERS.H CONTAINS TIMER CLASS IMPLEMENTATION.

THE FILE CONTENT HAS BEEN CREATED TO SUPPORT "DEVELOPMENT OF FLIGHT
CONTROL SYSTEM FOR MORPHING ELEVON CONTROL SURFACE", 2019 THESIS.

FILE UTMOST REVIEW DONE ON (10.01.2020) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CORE_TIMER_HPP
#define ATL_CORE_TIMER_HPP

#include "Core.hpp"

#include <chrono>

namespace atl
{
	using Clock			= std::chrono::high_resolution_clock;
	using TimePoint		= std::chrono::time_point< Clock >;

	//-----------------------------------------------------------------------
	// TIMER
	//
	// Based on high_resolution_clock clock.
	//
	// Conversion units:
	// 1s = 1000ms 		(milli-seconds)
	// 1s = 1000000us 	(micro-seconds)
	// 1s = 1e+9ns		(nano-seconds)
	//-----------------------------------------------------------------------

	class CTimer
	{
	public:
		CTimer();

		void start() { m_startTP = m_clock.now(); }

		void reset() { this->start(); }

		// Returns elapsed time in seconds.
		double getElapsedTimeS();

		// Returns elapsed time in milliseconds.
		int64 getElapsedTimeMs();

		// Returns elapsed time in microseconds.
		int64 getElapsedTimeUs();
	
		// Returns elapsed time in nanoseconds.
		int64 getElapsedTimeNs();

	private:
		Clock m_clock;
		TimePoint m_startTP;
		TimePoint m_endTP;
	};

} // namespace atl
#endif // !ATL_CORE_TIMER_HPP
