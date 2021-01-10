#ifndef ATL_COMMS_GENERAL_HPP
#define ATL_COMMS_GENERAL_HPP

#include <assert.h>

namespace atl
{
    //-----------------------------------------------------------------------
	// AIR DATA
    //
    // Data to sent from UAV drone to the Ground Station
    //
    // ***** TODO: Consider using halffloat
	//-----------------------------------------------------------------------
    
    struct AirData48
    {
        float altitude;
        float airspeed;
        float heading;

        float pitch;
        float roll;
        float yaw;

        float pitchRate;
        float rollRate;
        float yawRate;

        float desiredAlttitude;
        float desiredAirspeed;
        float desiredHeading; 
    };

    static_assert( sizeof(AirData48) == 48, "AirData48 must be the size of 48!" );

} // namespace atl
#endif // !ATL_COMMS_GENERAL_HPP