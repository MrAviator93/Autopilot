/***********************************************************************
FILE DYNAMICS.HPP CONTAINS DYNAMIC ADDITIONS

FILE UTMOST REVIEW DONE ON (10.01.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_DYNAMICS_HPP
#define ATL_DYNAMICS_HPP

#include "Math.hpp"

namespace atl
{
	//-----------------------------------------------------------------------
	// DYNAMICS
	//
	// Contains mathematical equations for dynamical characteristic calculations.
	//-----------------------------------------------------------------------

	class CDynamics
	{
	public:

		// Estimates Earths Gravity at specific altitude [m]
		static inline scalar estimateEarthsGravityAtAltM(const scalar altitudeM);

		// Estimates Earths Gravity at specific altitude [km]
		static inline scalar estimateEarthsGravityAtAltKM(const scalar altitudeKM);

		// Calculates Speed of Sound (a) at specific altitude,
		// input:	temperature at specific altitude in Kelvins
		static inline scalar calcSpeedOfSoundAtAlt(const scalar tempAtAltK);

		// Calculates the Mach Number, M = V/a, 
		// input:	velocity [m/s], speed of sound [m/s]
		static inline scalar calcMachNumber(const scalar velocityMS, const scalar speedOfSoundMS);

		// Calculates Dynamic Pressure (q),
		// input:	density [kg/m^3], velocity [m/s]
		static inline scalar calcDynamicPressure(const scalar density, const scalar velocityMS);

		// Calculates Reynolds Number (Re),
		// input:	density [kg/m^3],
		//			velocity [m/s], 
		//			distance [m], 
		//			dynamic vic. [kg* m^-1 * s^-1]
		static inline scalar calcReynoldsNumber(
			const scalar density,
			const scalar velocity,
			const scalar distance,
			const scalar dynamicViscosity);

		// Calculates wing aspect ratio, input: Wing Span [m], Wing Area [m^2]
		static inline scalar calcWingAspectRatio(const scalar wingSpanM, const scalar wingAreaM2);

		// Calculates H-Tail Volume Ratio Coef. VH, 
		// input:	Horizontal Tail Area [m^2], 
		//			distance [m], 
		//			MAC [m], 
		//			Wing Area [m^2]
		static inline scalar calcHorizontalTailVolumeRatio(
			const scalar horizontalTailArea,
			const scalar lt,
			const scalar MAC,
			const scalar wingArea);

		// Calculates V-Tail Volume Ratio Coef. VT,
		// input:	Vertical Tail Area [m^2], 
		//			distance [m], 
		//			Wing Span [m], 
		//			Wing Area [m^2]
		static inline scalar calcVerticalTailVolumeRatio(
			const scalar verticalTailArea,
			const scalar lv,
			const scalar wingSpan,
			const scalar wingArea);

		// Calculates Lift to Drag Ratio (L/D)
		// input:	Coefficient of Lift (Cl), Coefficient of Drag (Cd)
		static inline scalar calcLiftToDragRatio(const scalar coefOfLift, const scalar coefOfDrag);

		// Estimates Lift Due to Angle of Attack (CLAlpha), 
		// also known as Lift Curve Slope, 
		// output [1/rad]
		// input:	Wing Aspect Ration (AR)
		static inline scalar estimateLiftDueToAoA(const scalar wingAspectRatio);

		// Estimates Drag Due to Angle of Attack (CDAlpha),
		// also known as Drag Curve Slope,
		// output [1/rad]
		// input:	Coefficient of Lift (Cl), 
		//			Oswald Efficiency Number (e), 
		//			Wing Aspect Ratio (AR),
		//			Lift Due to AoA (ClAlpha)
		static inline scalar estimateDragDueToAoA(
			const scalar coeficientOfLift,
			const scalar oswaldEfficiencyNumber,
			const scalar wingAspectRatio,
			const scalar liftDueToAngleOfAttack); //(CLAlpha)

		// Estimates Change in Down wash Due to Angle of Attack (dε/dα)
		// input:	Lift Due to AoA (ClAlpha), Wing Aspect Ratio (AR)
		static inline scalar estimateChangeInDownwashDueToAoA(
			const scalar liftDuetoAngleOfAttack,
			const scalar wingAspectRatio);
	};

} // namespace atl
#endif // !ATL_DYNAMICS_HPP