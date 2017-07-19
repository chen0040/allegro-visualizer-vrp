#ifndef _H_BEHAVIOR_STATION_H
#define _H_BEHAVIOR_STATION_H

#include "Behavior.h"

/// <summary>Class that represents the behavior of a customer</summary>
class Behavior_Station : public Behavior
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] pOwner the customer game agent
	Behavior_Station(BaseGameEntity* pOwner);
	/// <summary>Destructor method</summary>
	virtual ~Behavior_Station();

public:
	/// <summary>Method that update the station game agent when the timer ticks in the game engine</summary>
	/// \param[in] deltaTime the time interval between two consecutive calls to update method
	virtual void Update(float deltaTime);
	/// <summary>Method that render the images and drawings associated with the game agent</summary>
	/// \param[in] buffer the buffer image onto which the images and drawings associated with the customer agent are rendered and displayed using double-buffer techniques
	virtual void Render(BITMAP* buffer);

public:
	/// <summary>Method that sets the remaining unfulfilled demand of the customer</summary>
	/// \param[in] d the remaining unfulfilled demand of the customer
	void SetRemainingDemand(float d) { m_remaining_demand=d; }
	/// <summary>Method that sets the demand of the customer</summary>
	/// \param[in] d the demand of the customer
	void SetDemand(float d) { m_demand=d; }
	/// <summary>Method that reduce the current demand of the customer by a certain amount</summary>
	/// \param[in] d the amount to be reduced from the current demand of the customer
	void ChangeRemainingDemandBy(float d);
	/// <summary>Method that returns the remaining demand of the customer</summary>
	/// <returns>The remaining demand of the customer</returns>
	float GetRemainingDemand() { return m_remaining_demand; }
	/// <summary>Method taht returns the remaining demand as the percentage of the total demand of the customer</summary>
	/// <returns>The percentage of the remaining demand in the total demad of the customer</returns>
	float GetRemainingDemandInPercentage() { return m_remaining_demand / m_demand; }
	/// <summary>Method taht returns the total demand of the customer</summary>
	/// <returns>The total demand of the customer</returns>
	float GetDemand() { return m_demand; }

public:
	/// <summary>Method that set the demand to be fulfilled for the customer</summary>
	void Request() { m_remaining_demand=m_demand; }

private:
	/// <summary>The remaining demand of the customer</summary>
	float m_remaining_demand;
	/// <summary>The total demand of the customer</summary>
	float m_demand;
};
#endif