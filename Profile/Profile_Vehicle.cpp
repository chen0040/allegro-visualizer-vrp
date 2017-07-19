#include "Profile_Vehicle.h"

/// <summary>Constructor method</summary>
/// \param[in] id the profile id
Profile_Vehicle::Profile_Vehicle(std::string id) : Profile(id)
{
	SetType("vehicle");
}

/// <summary>Destructor method</summary>
Profile_Vehicle::~Profile_Vehicle()
{

}
