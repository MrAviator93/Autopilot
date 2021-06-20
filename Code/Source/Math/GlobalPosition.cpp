#include "GlobalPosition.hpp"

namespace ATL::Core::Math
{
GlobalPosition::GlobalPosition( const GlobalPosition& globalPos )
{
	latitude = globalPos.latitude;
	longtitude = globalPos.longtitude;
}

GlobalPosition::GlobalPosition( double latitude, double longitude )
{
	this->latitude = latitude;
	this->longtitude = longitude;
}

GlobalPosition::GlobalPosition( float degLat, float minLat, float secLat, float degLon, float minLon, float secLon )
{
	latitude = static_cast< double >( degLat ) + static_cast< double >( minLat / 60.0 ) +
			   static_cast< double >( secLat / 3600.0 );

	longtitude = static_cast< double >( degLon ) + static_cast< double >( minLon / 60.0 ) +
				 static_cast< double >( secLon / 3600.0 );
}

GlobalPosition& GlobalPosition::operator=( const GlobalPosition& globalPos )
{
	latitude = globalPos.latitude;
	longtitude = globalPos.longtitude;
	return *this;
}

} // namespace ATL::Core::Math