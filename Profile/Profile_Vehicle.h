#ifndef _H_PROFILE_VEHICLE_H
#define _H_PROFILE_VEHICLE_H

#include "Profile.h"

/// <summary>Class that represents the profile of a vehicle agent</summary>
class Profile_Vehicle : public Profile
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] id the profile id
	Profile_Vehicle(std::string id);
	/// <summary>Destructor method</summary>
	virtual ~Profile_Vehicle();

};
#endif
