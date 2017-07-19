#include "Frame.h"
#include "../ImageManager/ImageManager.h"
#include <cmath>

/// <summary>Constructor method</summary>
/// \param[in] filename the path to the image file
Frame::Frame(std::string filename)
{
	SimulatorImageManager->LoadImageFromFile(filename);
	m_bmp=SimulatorImageManager->GetImage(filename);
	m_scaled=0.5;
}

/// <summary>Constructor method</summary>
/// \param[in] filename the path to the image file
/// \param[in] scaled the degree of image scaling
Frame::Frame(std::string filename, float scaled)
{
	SimulatorImageManager->LoadImageFromFile(filename);
	m_bmp=SimulatorImageManager->GetImage(filename);
	m_scaled=scaled;
}

/// <summary>Destructor method</summary>
Frame::~Frame()
{
	m_bmp=NULL;
}

/// <summary>Method that render the image of the sprite frame</summary>
/// \param[in] buffer the image buffer onto which the sprite frame draw and later displayed using the double-buffer techniques
/// \param[in] center the position of the sprite on the 2D screen
/// \param[in] angle the rotation angle of the sprite
void Frame::Render(BITMAP* buffer, Point2D center, fixed angle)
{
	//pivot_sprite(buffer, m_bmp, center.GetX(), center.GetY(), m_bmp->w/2, m_bmp->h/2, fixed_angle);
	pivot_scaled_sprite(buffer, m_bmp, center.GetX(), center.GetY(), m_bmp->w/2, m_bmp->h/2, angle, ftofix(m_scaled));
}
