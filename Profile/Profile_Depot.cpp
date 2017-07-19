#include "Profile_Depot.h"

/// <summary>Constructor method</summary>
/// \param[in] id the profile id
Profile_Depot::Profile_Depot(std::string id) : Profile(id)
{
	SetType("depot");
}

/// <summary>Destructor method</summary>
Profile_Depot::~Profile_Depot()
{

}
