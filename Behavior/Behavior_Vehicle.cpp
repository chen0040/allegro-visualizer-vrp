#include "Behavior_Vehicle.h"
#include "../GameEntity/BaseGameEntity.h"
#include "../Behavior/Behavior_Station.h"
#include <cmath>
#include <sstream>

/// <summary>Constructor method</summary>
/// \param[in] pOwner the vehicle game agent
Behavior_Vehicle::Behavior_Vehicle(BaseGameEntity* pOwner) : Behavior(pOwner), m_Active(false), m_speed(10), m_capacity(0), m_pause(0.3f), m_remaining_pause(0.0f)
{
	GetOwner()->GetAnimation()->SetCurrent("images\\vehicle.bmp");
}	

/// <summary>Destructor method</summary>
Behavior_Vehicle::~Behavior_Vehicle()
{
	m_pStationsToVisit.clear();
	m_pVisitedStations.clear();
}

/// <summary>Method that update the game agent when the timer ticks in the game engine</summary>
/// \param[in] deltaTime the time interval between two consecutive calls to the update method
void Behavior_Vehicle::Update(float deltaTime)
{
	if(m_pVisitedStations.empty())
	{
		GetOwner()->GetAnimation()->SetVisible(false);
		m_Active=false;
		return;
	}

	if(m_remaining_pause > 0)
	{
		m_remaining_pause-=deltaTime;

		if(m_pVisitedStations.front()->GetProfile()->GetType()=="station")
		{
			Behavior_Station* pBehavior=dynamic_cast<Behavior_Station*>(m_pVisitedStations.front()->GetBehavior());

			float fd=pBehavior->GetDemand() * deltaTime / m_pause;
			m_remaining_load-=fd;
			pBehavior->ChangeRemainingDemandBy(-fd);
		}

		if(m_remaining_pause <= 0)
		{
			if(m_pVisitedStations.front()->GetProfile()->GetType()=="station")
			{
				Behavior_Station* pBehavior=dynamic_cast<Behavior_Station*>(m_pVisitedStations.front()->GetBehavior());
				
				m_pVisitedStations.front()->GetAnimation()->SetCurrent("images\\shell_normal.bmp");

				std::ostringstream oss;
				oss << GetOwner()->GetProfile()->GetID() << " Leaving {" << m_pVisitedStations.front()->GetProfile()->GetID() << "}";
				m_message=oss.str();
			}
			m_pVisitedStations.pop_front();
		}
		return;
	}
	
	float mov_dist=m_speed * deltaTime;

	BaseGameEntity* pStation=m_pVisitedStations.front();

	Point2D posStation=pStation->GetBehavior()->GetPosition();
	Point2D disp=posStation-GetPosition();

	float dist=disp.Length();
	Point2D vec=disp.Normalize();
	
	if(dist <= mov_dist)
	{ 
		SetAngle(0);
		SetPosition(posStation);
		if(pStation->GetProfile()->GetType()=="station")
		{
			pStation->GetAnimation()->SetCurrent("images\\shell_over.bmp");
		}
		else if(pStation->GetProfile()->GetType()=="depot")
		{
		}

		std::ostringstream oss;
		oss << GetOwner()->GetProfile()->GetID() << " Arrived at {" << pStation->GetProfile()->GetID() << "}";
		m_message=oss.str();
		Pause();
	}
	else
	{
		fixed ang=fixatan2(disp.GetY(), disp.GetX());
		SetAngle(ang);

		SetPosition(GetPosition()+vec * mov_dist);

		std::ostringstream oss;
		oss << GetOwner()->GetProfile()->GetID() << " Moving to {" << pStation->GetProfile()->GetID() << "}";

		m_message=oss.str();
	}
}

/// <summary>Method that renders the images and drawings of the vehicle agent</summary>
/// \param[in] buffer the image buffer onto which the images and drawings of the vehicle agent are rendered and displayed using the double-buffer techniques
void Behavior_Vehicle::Render(BITMAP* buffer)
{
	
}

/// <summary>Method that add the customer agent visited by the vehicle agent to its route</summary>
/// \param[in] pStation the customer agent added to the vehicle's route
void Behavior_Vehicle::AddStationToVisit(BaseGameEntity* pStation)
{
	m_pStationsToVisit.push_back(pStation);
}

/// <summary>Method that renders the path of the vehicle agent</summary>
/// \param[in] buffer the image buffer onto which the images and drawings of the vehicle agent are rendered and displayed using the double-buffer techniques
/// \param[in] clr1 the color of the path
void Behavior_Vehicle::RenderPath(BITMAP* buffer, int clr1)
{
	for(unsigned int i=0; i<m_pStationsToVisit.size()-1; i++)
	{
		Point2D pos1=m_pStationsToVisit[i]->GetScreenPosition();
		Point2D pos2=m_pStationsToVisit[i+1]->GetScreenPosition();

		line(buffer, pos1.GetX(), pos1.GetY(), pos2.GetX(), pos2.GetY(), clr1);
	}
}

/// <summary>Method that start the engine of the vehicle agent</summary>
void Behavior_Vehicle::Start()
{
	GetOwner()->GetAnimation()->SetVisible(true);
	m_Active=true;
	m_remaining_pause=0.0f;
	m_remaining_load=m_capacity;
	
	m_pVisitedStations.clear();
	std::vector<BaseGameEntity*>::iterator pos1;
	for(pos1=m_pStationsToVisit.begin(); pos1!=m_pStationsToVisit.end(); ++pos1)
	{
		BaseGameEntity* pStation=*pos1;

		if(pStation->GetProfile()->GetType()=="station")
		{
			Behavior_Station* pBehavior=dynamic_cast<Behavior_Station*>(pStation->GetBehavior());
			pBehavior->Request();
		}
		m_pVisitedStations.push_back(pStation);
	}

	SetPosition(m_pVisitedStations.front()->GetBehavior()->GetPosition());
	m_pVisitedStations.pop_front();
	
	std::ostringstream oss;
	oss << GetOwner()->GetProfile()->GetID() << " Started";

	m_message=oss.str();
}
