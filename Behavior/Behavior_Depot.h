#ifndef _H_BEHAVIOR_DEPOT_H
#define _H_BEHAVIOR_DEPOT_H

#include "Behavior.h"

/// <summary>Class that represents the behavior of a depot</summary>
class Behavior_Depot : public Behavior
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] pEntity the depot game agent
	Behavior_Depot(BaseGameEntity* pEntity);
	/// <summary>Destructor method</summary>
	virtual ~Behavior_Depot();

public:
	/// <summary>Method that update the depot when the timer ticks in the game engine</summary>
	/// \param[in] deltaTime the time interval between two consecutive calls to the update method
	virtual void Update(float deltaTime);
	/// <summary>Method that render the images and drawing associated with the behavior of game agent</summary>
	/// \param[in] buffer the image buffer onto which the images and drawings associated with the game agent are rendered and diplayed using the double-buffer technique
	virtual void Render(BITMAP* buffer);

};
#endif