/***********************************************************************
FILE ISADATA.HPP CONTAINS INTERNATIONAL STANDARD ATMOSPHERE DATA ENTRIES

FILE UTMOST REVIEW DONE ON (08.01.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_ISA_DATA_HPP
#define ATL_ISA_DATA_HPP

#include "Core.hpp"

#include <array>

namespace atl
{
	//-----------------------------------------------------------------------
	// INTERNATIONAL STANDARD ATMOSPHERE (ISA) ENTRY
	//
	// Consists of 9 entries
	//-----------------------------------------------------------------------

	struct ISADataEntry
	{
		scalar heightFt;
		scalar heightM;
		scalar theta;			// Temperature divided by sea - level temperature.
		scalar temperatureK;
		scalar temperatureC;
		scalar delta;			// Pressure divided by sea - level pressure.
		scalar pressure;		// [N/m^2]
		scalar sigma;			// Density divided by sea - level density.
		scalar airDensity;		// [kg/m^3]
	};

	const static std::array<ISADataEntry, 310> ISA_TABLE_DATA =
	{
		ISADataEntry{ -2000.0, -609.6, 1.0138, 292.11, 18.96, 1.0744, 108866, 1.0598, 1.2983 },
		ISADataEntry{ -1800.0, -548.6, 1.0124, 291.72, 18.57, 1.0668, 108092, 1.0537, 1.2908 },
		// ****** TODO: To be completed ...

	};

} // namespace atl
#endif // !ATL_ISA_DATA_HPP