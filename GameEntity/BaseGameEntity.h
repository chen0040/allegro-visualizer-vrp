#ifndef _H_BASE_GAME_ENTITY_H
#define _H_BASE_GAME_ENTITY_H

#include "../Animation/Animation.h"
#include "../Behavior/Behavior.h"
#include "../Profile/Profile.h"
#include "../allegro_include/allegro.h"

/// <summary>Class that represents a game engine in the game world</summary>
class BaseGameEntity
{
public:
	/// <summary>Constructor method</summary>
	BaseGameEntity();
	/// <summary>Destructor method</summary>
	virtual ~BaseGameEntity();

public:
	/// <summary>Method that renders the image and drawing associated with the game agent</summary>
	/// \param[in] buffer the image buffer onto which the images and drawings associated with the game agent are rendered and displayed as the double-buffer technique
	void Render(BITMAP* buffer);
	/// <summary>Method that update the game agent when the timer ticks in the game engine</summary>
	/// \param[in] deltaTime the time duration between two consecutive calls to the update method
	void Update(float deltaTime);

public:
	/// <summary>Method that sets the behavior of the game agent</summary>
	/// \param[in] pBehavior the behvior expressed by the game agent
	void SetBehavior(Behavior* pBehavior);
	/// <summary>Method that returns the behavior expressed by the game agent</summary>
	/// <returns>the behavior expressed by the game agent</returns>
	Behavior* GetBehavior() { return m_pBehavior; }

public:
	/// <summary>Method that sets the profile of the game agent</summary>
	/// \param[in] pProfile the profile representing the game agent
	void SetProfile(Profile* pProfile);
	/// <summary>Method that return the profile of the game agent</summary>
	/// <returns>The profile of the game agent</returns>
	Profile* GetProfile() { return m_pProfile; }

public:
	/// <summary>Method that returns the position of the game agent</summary>
	/// <returns>The position of the game agent</returns>
	Point2D GetScreenPosition();

public:
	/// <summary>Method that returns the animation sequencer of the game agent</summary>
	/// <returns>The animation sequencer of the game agent</returns>
	Animation* GetAnimation() { return m_pAnimation;  }

private:
	/// <summary>The animation sequencer of the game agent</summary>
	Animation* m_pAnimation;
	/// <summary>The behavior of the game agent</summary>
	Behavior* m_pBehavior;
	/// <summary>The profile of the game agent</summary>
	Profile* m_pProfile;

};
#endif