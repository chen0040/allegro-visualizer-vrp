#ifndef _H_PROFILE_STATION_H
#define _H_PROFILE_STATION_H

#include "Profile.h"

/// <summary>Class that represents the profile of a customer</summary>
class Profile_Station : public Profile
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] id the profile id 
	Profile_Station(std::string id);
	/// <summary>Destructor method</summary>
	virtual ~Profile_Station();

public:
	/// <summary>Method that set the demand of a customer</summary>
	/// \param[in] demand the demand of a customer
	void SetDemand(float demand) { m_demand=demand; }
	/// <summary>Method that returns the demand of a customer</summary>
	/// <returns>The demand of a customer</returns>
	float GetDemand() { return m_demand; }
private:
	/// <summary>The demand of a customer</summary>
	float m_demand;
};
#endif