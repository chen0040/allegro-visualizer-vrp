#ifndef _H_BEHAVIOR_VEHICLE_H
#define _H_BEHAVIOR_VEHICLE_H

#include "Behavior.h"
#include <list>
#include <vector>

/// <summary>Class that represents the behavior expressed by the vehicle agent</summary>
class Behavior_Vehicle : public Behavior
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] pOwner the vehicle game agent
	Behavior_Vehicle(BaseGameEntity* pOwner);
	/// <summary>Destructor method</summary>
	virtual ~Behavior_Vehicle();

public:
	/// <summary>Method that update the game agent when the timer ticks in the game engine</summary>
	/// \param[in] deltaTime the time interval between two consecutive calls to the update method
	virtual void Update(float deltaTime);
	/// <summary>Method that renders the images and drawings of the vehicle agent</summary>
	/// \param[in] buffer the image buffer onto which the images and drawings of the vehicle agent are rendered and displayed using the double-buffer techniques
	virtual void Render(BITMAP* buffer);

public:
	/// <summary>Method that renders the path of the vehicle agent</summary>
	/// \param[in] buffer the image buffer onto which the images and drawings of the vehicle agent are rendered and displayed using the double-buffer techniques
	/// \param[in] clr1 the color of the path
	void RenderPath(BITMAP* buffer, int clr1);

public:
	/// <summary>Method that add the customer agent visited by the vehicle agent to its route</summary>
	/// \param[in] pStation the customer agent added to the vehicle's route
	void AddStationToVisit(BaseGameEntity* pStation);

public:
	/// <summary>Method that set the speed of the vehicle agent</summary>
	/// \param[in] speed the new value of vehicle speed
	void SetSpeed(float speed) { m_speed=speed; }
	/// <summary>Method taht set the capacity of the vehicle agent</summary>
	/// \param[in] c the new value of vehicle capacity
	void SetCapacity(float c) { m_capacity=c; }

public:
	/// <summary>Method that start the engine of the vehicle agent</summary>
	void Start();
	/// <summary>Method that indicate whether the vehicle agent reach the end of its route, i.e. whether it returns to the depot</summary>
	/// <returns>The boolean flag indicating whether the vehicle agent reach the end of its route</returns>
	bool IsEnded() { return !m_Active; }
	/// <summary>Method that indicate whether the vehicle agent is moving on its route</summary>
	/// <returns>The boolean flag indicating whether the vehicle agent is moving on its route</returns>
	bool IsMoving() { return m_Active && m_remaining_pause <= 0.0f; }

public:
	/// <summary>Method that pause the vehicle agent at a customer agent</summary>
	void Pause() { m_remaining_pause=m_pause; }
	/// <summary>Method that set the duration of pause for the vehicle agent at a customer agent</summary>
	void SetPauseInterval(float p) { m_pause=p; }

public:
	/// <summary>Method that returns the remaining resource still loaded in the vehicle</summary>
	/// <returns>the remainign source still loaded in the vehicle</returns>
	float GetRemainingLoad() { return m_remaining_load; }
	/// <summary>Method that returns the remaining resource still loaded in the vehicle as the percentage of the total capacity of the vehicle</summary>
	/// <returns>The percentage of the remaining resourc still loaded in the vehicle in the total capacity of the vehicle</returns>
	float GetRemainingLoadInPercentage() { return m_remaining_load / m_capacity; }

public:
	/// <summary>Method that returns the description of the vehicle agent</summary>
	std::string ToString() { return m_message; }

private:
	/// <summary>Customers that have already visited by the vehicle agent</summary>
	std::list<BaseGameEntity*> m_pVisitedStations;
	/// <summary>Customers that are yet to be visited by the vehicle agent</summary>
	std::vector<BaseGameEntity*> m_pStationsToVisit;

	/// <summary>Whether engine of the vehicle is on</summary>
	bool m_Active;

	/// <summary>The capacity of the vehicle</summary>
	float m_capacity;
	/// <summary>The speed of the vehicle</summary>
	float m_speed;

	/// <summary>Whether the vehicle is paused at a customer agent</summary>
	float m_pause;
	/// <summary>The duration of pause still to be completed by the vehicle agent at a customer agent</summary>
	float m_remaining_pause;

	/// <summary>The remaining sources still loaded in the vehicle</summary>
	float m_remaining_load;

	/// <summary>The description of the vehicle agent</summary>
	std::string m_message;
};
#endif