#include "Profile_Station.h"

/// <summary>Constructor method</summary>
/// \param[in] id the profile id
Profile_Station::Profile_Station(std::string id) : Profile(id)
{
	SetType("station");
}

/// <summary>Destructor method</summary>
Profile_Station::~Profile_Station()
{

}

