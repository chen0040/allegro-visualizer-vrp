#include "Behavior_Depot.h"
#include "../GameEntity/BaseGameEntity.h"

Behavior_Depot::Behavior_Depot(BaseGameEntity* pOwner) : Behavior(pOwner)
{
	GetOwner()->GetAnimation()->SetCurrent("images\\depot.bmp", 2.0f);
}

/// <summary>Destructor method</summary>
Behavior_Depot::~Behavior_Depot()
{

}

/// <summary>Method that update the depot when the timer ticks in the game engine</summary>
/// \param[in] deltaTime the time interval between two consecutive calls to the update method
void Behavior_Depot::Update(float deltaTime)
{

}

/// <summary>Method that render the images and drawing associated with the behavior of game agent</summary>
/// \param[in] buffer the image buffer onto which the images and drawings associated with the game agent are rendered and diplayed using the double-buffer technique
void Behavior_Depot::Render(BITMAP* buffer)
{

}
