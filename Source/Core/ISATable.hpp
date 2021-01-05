/***********************************************************************
FILE ISATABLE.H CONTAINS ITERNATIONAL STANDART TABLE IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (04.01.2021) BY ARTUR K. 
***********************************************************************/

#ifndef ATL_ISA_TABLE_HPP
#define ATL_ISA_TABLE_HPP

#include "ISAData.hpp"

namespace atl
{
	//-----------------------------------------------------------------------
	// INTERNATIONAL STANDARD ATMOSPHERE (ISA) TABLE
	//-----------------------------------------------------------------------

	class CISATable
	{
	public:
		static CISATable& getInstance()
		{
			static CISATable instance;
			return instance;
		}

		// ****** TODO: Implement functionality
		scalar getTemperatureK(const scalar heightM) const { return 0.0; }
		scalar getTemperatureC(const scalar heightM) const { return 0.0; }
		scalar getPressureNM2(const scalar heightM) const { return 0.0; }
		scalar getAirDensityKGM3(const scalar heightM) const { return 0.0; }

	private:
		CISATable() = default;
		~CISATable() = default;
		CISATable(const CISATable&) = delete;
		CISATable& operator=(const CISATable&) = delete;
		CISATable(const CISATable&&) = delete;
		CISATable& operator=(const CISATable&&) = delete;
	};

} // namespace atl
#endif // !ATL_ISA_TABLE_HPP
