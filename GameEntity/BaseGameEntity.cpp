#include "BaseGameEntity.h"
#include "../SceneManager/SceneManager.h"
#include "../Application/Application.h"
#include "../Util/Rect2D.h"
#include <cassert>

/// <summary>Constructor method</summary>
BaseGameEntity::BaseGameEntity() : m_pBehavior(NULL), m_pProfile(NULL)
{
	m_pAnimation=new Animation();
}

/// <summary>Destructor method</summary>
BaseGameEntity::~BaseGameEntity()
{
	if(m_pAnimation!=NULL)
	{
		delete m_pAnimation;
		m_pAnimation=NULL;
	}
	if(m_pBehavior!=NULL)
	{
		delete m_pBehavior;
		m_pBehavior=NULL;
	}
	if(m_pProfile!=NULL)
	{
		delete m_pProfile;
		m_pProfile=NULL;
	}
}

/// <summary>Method that renders the image and drawing associated with the game agent</summary>
/// \param[in] buffer the image buffer onto which the images and drawings associated with the game agent are rendered and displayed as the double-buffer technique
void BaseGameEntity::Render(BITMAP* buffer)
{
	if(m_pBehavior!=NULL)
	{
		Point2D pos=GetScreenPosition();
		fixed angle=m_pBehavior->GetAngle();

		m_pAnimation->Render(buffer, pos, angle);
		m_pBehavior->Render(buffer);
	}
}

/// <summary>Method that update the game agent when the timer ticks in the game engine</summary>
/// \param[in] deltaTime the time duration between two consecutive calls to the update method
void BaseGameEntity::Update(float deltaTime)
{
	if(m_pBehavior!=NULL)
	{
		m_pBehavior->Update(deltaTime);
	}
}

/// <summary>Method that sets the behavior of the game agent</summary>
/// \param[in] pBehavior the behvior expressed by the game agent
void BaseGameEntity::SetBehavior(Behavior* pBehavior)
{
	if(m_pBehavior!=NULL)
	{
		delete m_pBehavior;
		m_pBehavior=NULL;
	}
	m_pBehavior=pBehavior; 
}

/// <summary>Method that sets the profile of the game agent</summary>
/// \param[in] pProfile the profile representing the game agent
void BaseGameEntity::SetProfile(Profile* pProfile)
{
	if(m_pProfile!=NULL)
	{
		delete m_pProfile;
		m_pProfile=NULL;
	}
	m_pProfile=pProfile;
}

/// <summary>Method that returns the position of the game agent</summary>
/// <returns>The position of the game agent</returns>
Point2D BaseGameEntity::GetScreenPosition()
{
	assert(m_pBehavior!=NULL);

	Point2D pos=m_pBehavior->GetPosition();

	Rect2D SimulatorActivityZone=SimulatorSceneManager->GetSimulatorActivityZone();

	pos-=Point2D(SimulatorActivityZone.left, SimulatorActivityZone.top);

	float ScreenWidth=SimulatorApp->GetWidth();
	float ScreenHeight=SimulatorApp->GetHeight();
	float offset_x=SimulatorApp->GetHorizontalOffset();
	float offset_y=SimulatorApp->GetVerticalOffset();
	ScreenWidth-=offset_x*2;
	ScreenHeight-=offset_y*2;

	pos=Point2D(pos.GetX() * ScreenWidth/ SimulatorActivityZone.Width() + SimulatorApp->GetLeft(), pos.GetY() * ScreenHeight / SimulatorActivityZone.Height()+SimulatorApp->GetTop());

	pos+=Point2D(offset_x, offset_y);

	return pos;
}
