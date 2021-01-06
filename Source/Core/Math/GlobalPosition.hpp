/***********************************************************************
FILE GLOBALPOSITION.H CONTAINS GLOBAL POSITION OBJECT IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (06.01.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_GLOBAL_POSITION_HPP
#define ATL_GLOBAL_POSITION_HPP

#include "Core.hpp"

namespace atl
{
	//-----------------------------------------------------------------------
	// GLOBAL POSITION 
	//
	// Note that float is inapplicable for latitude and longitude calculations.
	//-----------------------------------------------------------------------

	struct GlobalPosition
	{
		GlobalPosition() = default;

		GlobalPosition(const GlobalPosition& globalPos);

		GlobalPosition(double latitude, double longitude);

		GlobalPosition(
			float degLat, float minLat, float secLat,
			float degLon, float minLon, float secLon);

		~GlobalPosition() = default;

		GlobalPosition& operator= (const GlobalPosition& globalPos);

		double latitude{ 0.0 };
		double longtitude{ 0.0 };
	};

	//-----------------------------------------------------------------------
	// WAY-POINT
	//
	// To be used in navigation system (must be moved to a separate file!
	// Waypoints must be stored in a std::list<WayPoint> data structure !!!
	//
	// flags		- Reserved for future use (way-point could have a specific action such as drop a weight, etc.)
	// altitudeM	- Altitude to be reached at this specific function
	// worldPos		- World or Global position of the way-point
	//-----------------------------------------------------------------------

	struct WayPoint
	{
		uint32				flags{ 0 };
		float				altitudeM{ 0.0 };
		GlobalPosition		worldPos{ 0.0, 0.0 };
	};

} // namespace atl
#endif // !ATL_GLOBAL_POSITION_HPP
