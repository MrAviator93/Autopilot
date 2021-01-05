#include "Dynamics.hpp"

namespace atl
{
	inline scalar CDynamics::estimateEarthsGravityAtAltM(const scalar altitudeM)
	{
		return (EARTHS_GRAVITY / CMath::pow2((EARTH_RADIUS_M + altitudeM) / EARTH_RADIUS_M));
	}

	inline scalar CDynamics::estimateEarthsGravityAtAltKM(const scalar altitudeKM)
	{
		return (EARTHS_GRAVITY / CMath::pow2((EARTH_RADIUS_KM + altitudeKM) / EARTH_RADIUS_KM));
	}

	inline scalar CDynamics::calcSpeedOfSoundAtAlt(const scalar tempAtAltK)
	{
		return sqrt(RATIO_OF_SPECIFIC_AIR_CAPACITY * SPECIFIC_GAS_AIR_CONSTANT * tempAtAltK);
	}

	inline scalar CDynamics::calcMachNumber(const scalar velocityMS, const scalar speedOfSoundMS)
	{
		return (velocityMS / speedOfSoundMS);
	}

	inline scalar CDynamics::calcDynamicPressure(const scalar density, const scalar velocityMS)
	{
		return (0.5 * density * (velocityMS * velocityMS));
	}

	inline scalar CDynamics::calcReynoldsNumber(
		const scalar density,
		const scalar velocity,
		const scalar distance,
		const scalar dynamicViscosity)
	{
		return ((density * velocity * distance) / dynamicViscosity);
	}

	inline scalar CDynamics::calcWingAspectRatio(const scalar wingSpanM, const scalar wingAreaM2)
	{
		return ((wingSpanM * wingSpanM) / wingAreaM2);
	}

	inline scalar CDynamics::calcHorizontalTailVolumeRatio(
		const scalar horizontalTailArea,
		const scalar lt,
		const scalar MAC,
		const scalar wingArea)
	{
		// VH = SH x LH / SW x MAC
		return ((horizontalTailArea * lt) / (wingArea * MAC));
	}

	inline scalar CDynamics::calcVerticalTailVolumeRatio(
		const scalar verticalTailArea,
		const scalar lv,
		const scalar wingSpan,
		const scalar wingArea)
	{
		return ((verticalTailArea * lv) / (wingArea * wingSpan));
	}

	inline scalar CDynamics::calcLiftToDragRatio(const scalar coefOfLift, const scalar coefOfDrag)
	{
		return (coefOfLift / coefOfDrag);
	}

	inline scalar CDynamics::estimateLiftDueToAoA(const scalar wingAspectRatio)
	{
		// (2 * PI) / (1 + ((2 * PI) / (PI * AR) )), (Nelson, pg.145 also pg. 57)
		return ((2 * PI) / (1 + ((2 * PI) / (PI * wingAspectRatio))));
	}

	inline scalar CDynamics::estimateDragDueToAoA(
		const scalar coeficientOfLift,
		const scalar oswaldEfficiencyNumber,
		const scalar wingAspectRatio,
		const scalar liftDueToAngleOfAttack)
	{
		// ( (2 * Cl) / PI() * e * AR) * Clα
		return (((2 * coeficientOfLift) / (PI * oswaldEfficiencyNumber * wingAspectRatio)) * liftDueToAngleOfAttack);
	}

	inline scalar CDynamics::estimateChangeInDownwashDueToAoA(
		const scalar liftDuetoAngleOfAttack,
		const scalar wingAspectRatio)
	{
		// Nelson, pg.125
		return ((2 * liftDuetoAngleOfAttack) / (PI * wingAspectRatio));
	}

} // namespace atl