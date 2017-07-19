#ifndef _H_PROFILE_H
#define _H_PROFILE_H

#include <string>

/// <summary>Class that represent the profile of a game agent</summary>
class Profile
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] id of the profile
	Profile(std::string id);
	/// <summary>Destructor method</summary>
	virtual ~Profile() {}

private:
	/// <summary>The id of the profile</summary>
	std::string m_Id;
	/// <summary>The type of the profile</summary>
	std::string m_Type;

public:
	/// <summary>Method that returns the profie id</summary>
	/// <returns>The profile id</returns>
	std::string GetID() { return m_Id; }
	/// <summary>Method that sets the profile id</summary>
	/// \param[in] id the profile id
	void SetID(std::string id) { m_Id=id; }
	/// <summary>Method that returns type of profile</summary>
	/// <returns>The type of profile</returns>
	std::string GetType() { return m_Type; }
	/// <summary>Method set the type of profile</summary>
	/// \param[in] type the profile type
	void SetType(std::string type) { m_Type=type; }

};
#endif