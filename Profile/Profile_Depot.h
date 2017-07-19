#ifndef _H_PROFILE_DEPOT_H
#define _H_PROFILE_DEPOT_H

#include "Profile.h"

/// <summary>Class that represents the profile of a depot</summary>
class Profile_Depot : public Profile
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] id the profile id
	Profile_Depot(std::string id);
	/// <summary>Destructor method</summary>
	virtual ~Profile_Depot();
};
#endif