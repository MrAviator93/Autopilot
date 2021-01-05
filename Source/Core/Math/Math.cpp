#include "Math.hpp"

namespace atl
{
	inline scalar CMath::linearInterpolation(scalar y1, scalar y2, scalar x, scalar x1, scalar x2)
	{
		return y1 + ((x - x1) / (x2 - x1)) * (y2 - y1);
	}

	scalar CMath::calcDistHarversineM(scalar lat1, scalar lon1, scalar lat2, scalar lon2)
	{
		const scalar R = EARTH_RADIUS_M;
		scalar latRad1 = deg2rad(lat1);
		scalar latRad2 = deg2rad(lat2);
		scalar deltaLat = deg2rad(lat2 - lat1);
		scalar deltaLong = deg2rad(lon2 - lon1);

		scalar a = sin2(deltaLat / 2) +
			std::cos(latRad1) *
			std::cos(latRad2) *
			sin2(deltaLong / 2);

		scalar c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
		return (R * c);
	}

	scalar CMath::calcDistHarversineM(const GlobalPosition& p1, const GlobalPosition& p2)
	{
		const scalar R = EARTH_RADIUS_M;
		scalar latRad1 = deg2rad(p1.latitude);
		scalar latRad2 = deg2rad(p2.latitude);
		scalar deltaLat = deg2rad(p2.latitude - p1.latitude);
		scalar deltaLong = deg2rad(p2.longtitude - p1.longtitude);

		scalar a = sin2(deltaLat / 2) +
			std::cos(latRad1) *
			std::cos(latRad2) *
			sin2(deltaLong / 2);

		scalar c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
		return (R * c);
	}

	scalar CMath::calcInitialBearingDeg(const GlobalPosition& p1, const GlobalPosition& p2)
	{
		scalar latRad1 = deg2rad(p1.latitude);
		scalar latRad2 = deg2rad(p2.latitude);

		scalar lonRad1 = deg2rad(p1.longtitude);
		scalar lonRad2 = deg2rad(p2.longtitude);

		scalar deltaLong = deg2rad(p2.longtitude - p1.longtitude);

		scalar y = std::sin(lonRad2 - lonRad1) * std::cos(latRad2);

		scalar x =
			std::cos(latRad1) * std::sin(latRad2) -
			std::sin(latRad1) * std::cos(latRad2) * std::cos(lonRad2 - lonRad1);

		scalar theta = std::atan2(y, x);
		scalar bearing = (theta * 180.0 / PI + 360.0); // In degrees
		return bearing;
	}

} // namespace atl