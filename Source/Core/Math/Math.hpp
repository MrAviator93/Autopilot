/***********************************************************************
FILE FMATH.H CONTAINS ADDITIONAL MATH FUNCTIONS

Resources:
https://www.igismap.com/formula-to-find-bearing-or-heading-angle-between-two-points-latitude-longitude/
https://www.movable-type.co.uk/scripts/latlong.html
https://www.sunearthtools.com/tools/distance.php

FILE UTMOST REVIEW DONE ON 04.01.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_MATH_HPP
#define ATL_MATH_HPP

#include <Core.hpp>
#include "GlobalPosition.hpp"

#include <cmath>

#undef PI

namespace atl
{
	//-----------------------------------------------------------------------
	// CONSTANT DEFINITIONS
	//-----------------------------------------------------------------------

	const static scalar PI = 3.14159265;
	const static scalar EARTHS_GRAVITY = 9.80665;					// Nominal "average" value [m/s^2]
	const static scalar EARTH_RADIUS_M = 6371000.0;					// Nominal "average" value [km]
	const static scalar EARTH_RADIUS_KM = EARTH_RADIUS_M / 1000.0;	// Nominal "average" value [m] 

	const static scalar RATIO_OF_SPECIFIC_AIR_CAPACITY = 1.4;		// Polytropic exponent 
	const static scalar SPECIFIC_GAS_AIR_CONSTANT = 287.0;			// R [J/kg]

	//-----------------------------------------------------------------------
	// FMATH
	//
	// Contains additional mathematical functions.
	//-----------------------------------------------------------------------

	class CMath
	{
	public:

		static inline scalar pow2(scalar value) { return value * value; }
		static inline scalar pow3(scalar value) { return value * value * value; }
		static inline scalar pow4(scalar value) { return value * value * value * value; }

		static inline scalar deg2rad(scalar deg) { return (deg * PI / 180.0); }
		static inline scalar rad2deg(scalar rad) { return (rad * 180.0 / PI); }

		static inline scalar sin2(scalar value) { return (std::pow(std::sin(value), 2)); }
		static inline scalar cos2(scalar value) { return (std::pow(std::cos(value), 2)); }

		// Returns linearly interpolated y value
		static inline scalar linearInterpolation(scalar y1, scalar y2, scalar x, scalar x1, scalar x2);

		static scalar calcDistHarversineM(scalar lat1, scalar lon1, scalar lat2, scalar lon2);

		static scalar calcDistHarversineM(const GlobalPosition& p1, const GlobalPosition& p2);

		// For final bearing, simply take the initial bearing 
		// from the end point to the start point and reverse it (using θ = (θ + 180) % 360)
		static scalar calcInitialBearingDeg(const GlobalPosition& p1, const GlobalPosition& p2);
	};

} // namespace atl
#endif // !ATL_MATH_HPP
