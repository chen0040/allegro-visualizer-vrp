#ifndef _H_BEHAVIOR_H
#define _H_BEHAVIOR_H

#include "../Util/Point2D.h"
#include "../allegro_include/allegro.h"

class BaseGameEntity;

/// <summary>Class that represents the behavior of a game agent</summary>
class Behavior
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] pOwner the game agent that express the behavior
	Behavior(BaseGameEntity* pOwner);
	/// <summary>Destructor method</summary>
	virtual ~Behavior();

public:
	/// <summary>Method that ticks the timer, which is iteratively called within the game agent's update method</summary>
	/// \param[in] deltaTime the time interval between two consecutive calls to update
	virtual void Update(float deltaTime)=0;
	/// <summary>Method that renders images and drawing associated with the behavior</summary>
	/// \param[in] buffer the image buffer onto which the rendering is performend and displayed using the double-buffer technique
	virtual void Render(BITMAP* buffer)=0;

private:
	/// <summary>The position of the game agent</summary>
	Point2D m_Position;
	/// <summary>The rotation angle of the game agent</summary>
	fixed m_angle;
	/// <summary>The speed of the game agent</summary>
	float m_speed;
public:
	/// <summary>Method that returns the position of the game agent</summary>
	Point2D GetPosition() { return m_Position; }
	/// <summary>Method that returns the rotation angle of the game agent</summary>
	fixed GetAngle() { return m_angle; }
	/// <summary>Method that returns the speed of the game agent</summary>
	float GetSpeed() { return m_speed; }
public:
	/// <summary>Method that sets the position of the game agent</summary>
	/// \param[in] d the position of the game agent
	void SetPosition(Point2D d) { m_Position=d; }
	/// <summary>Method taht sets the speed of the game agent</summary>
	/// \param[in] sp the speed of the game agent
	void SetSpeed(float sp) { m_speed=sp; }
	/// <summary>Method taht sets teh rotation angle of the game agent</summary>
	/// \param[in] ang the rotation angle of the game agent
	void SetAngle(fixed ang) { m_angle=ang; }

public:
	/// <summary>Method that returns the game agent that express the behavior</summary>
	/// <returns>The game agent that express the behavior</returns>
	BaseGameEntity* GetOwner() { return m_pOwner; }


private:
	/// <summary>The game agent that express the behavior</summary>
	BaseGameEntity* m_pOwner;
};
#endif