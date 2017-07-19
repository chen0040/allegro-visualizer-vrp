#include "Behavior_Station.h"
#include "../GameEntity/BaseGameEntity.h"

/// <summary>Constructor method</summary>
/// \param[in] pOwner the customer game agent
Behavior_Station::Behavior_Station(BaseGameEntity* pOwner) : Behavior(pOwner), m_remaining_demand(0), m_demand(10)
{
	GetOwner()->GetAnimation()->SetCurrent("images\\shell_normal.bmp", 0.5f);
}

/// <summary>Destructor method</summary>
Behavior_Station::~Behavior_Station()
{

}

/// <summary>Method that update the station game agent when the timer ticks in the game engine</summary>
/// \param[in] deltaTime the time interval between two consecutive calls to update method
void Behavior_Station::Update(float deltaTime)
{

}

/// <summary>Method that render the images and drawings associated with the game agent</summary>
/// \param[in] buffer the buffer image onto which the images and drawings associated with the customer agent are rendered and displayed using double-buffer techniques
void Behavior_Station::Render(BITMAP* buffer)
{
	Point2D pos=GetOwner()->GetScreenPosition();
	rectfill(buffer, pos.GetX()-20, pos.GetY()+10, pos.GetX()-20+40* (1-GetRemainingDemandInPercentage()), pos.GetY()+15, makecol(0, 255, 0));
	rect(buffer, pos.GetX()-20, pos.GetY()+10, pos.GetX()+20, pos.GetY()+15, makecol(255, 0, 0));
	
}

/// <summary>Method that reduce the current demand of the customer by a certain amount</summary>
/// \param[in] d the amount to be reduced from the current demand of the customer
void Behavior_Station::ChangeRemainingDemandBy(float d)
{
	m_remaining_demand+=d;
	if(m_remaining_demand < 0)
	{
		m_remaining_demand=0;
	}
	if(m_remaining_demand > m_demand)
	{
		m_remaining_demand=m_demand;
	}
}
