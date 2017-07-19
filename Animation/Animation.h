#ifndef _H_ANIMATION_H
#define _H_ANIMATION_H

#include "Frame.h"
#include <map>
#include <string>
#include "../allegro_include/allegro.h"
#include "Frame.h"
#include "../Util/Point2D.h"

/// <summary>Class that represents the image animation sequence of a game agent</summary>
class Animation
{
public:
	/// <summary>Constructor method</summary>
	Animation();
	/// <summary>Destructor method</summary>
	virtual ~Animation();

public:
	/// <summary>Method that render the image of the game agent</summary>
	/// \param[in] buffer the image buffer onto which the image of the character is drawn and displayed using double-buffer technque
	/// \param[in] center the position of the character on the 2D screen
	/// \param[in] angle the rotation of the sprite image
	void Render(BITMAP* buffer, Point2D center, fixed angle);
	/// <summary>Method that set the current image of the sprite for the game agent</summary>
	/// \param[in] image_src the path to the image file
	void SetCurrent(std::string image_src);
	/// <summary>Method that set the current image of the sprite for the game agent</summary>
	/// \param[in] image_src the path to the image file
	/// \param[in] scaled_factor the image scaling factor
	void SetCurrent(std::string image_src, float scaled_factor);
	/// <summary>Method that set whether the sprite is visible</summary>
	/// \param[in] val the boolean flag indicating whether the sprite is visible
	void SetVisible(bool val);

private:
	/// <summary>The set of sprite frames included in the animation</summary>
	std::map<std::string, Frame*> m_frames;
	/// <summary>The current sprite image of the character</summary>
	Frame* m_pCurrentFrame;
	/// <summary>The boolean flag indicating whether the character is visible</summary>
	bool m_IsVisible;
};
#endif