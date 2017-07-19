#ifndef _H_FRAME_H
#define _H_FRAME_H

#include <string>
#include "../allegro_include/allegro.h"
#include "../Util/Point2D.h"

/// <summary>Class that represents a single sprite frame</summary>
class Frame
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] filename the path to the image file
	Frame(std::string filename);
	/// <summary>Constructor method</summary>
	/// \param[in] filename the path to the image file
	/// \param[in] scaled the degree of image scaling
	Frame(std::string filename, float scaled);
	/// <summary>Destructor method</summary>
	virtual ~Frame();

public:
	/// <summary>Method that render the image of the sprite frame</summary>
	/// \param[in] buffer the image buffer onto which the sprite frame draw and later displayed using the double-buffer techniques
	/// \param[in] center the position of the sprite on the 2D screen
	/// \param[in] angle the rotation angle of the sprite
	void Render(BITMAP* buffer, Point2D center, fixed angle);

private:
	/// <summary>Bitmap image of the sprite frame</summary>
	BITMAP* m_bmp;
	/// <summary>The degree of image scaling</summary>
	float m_scaled;

};
#endif