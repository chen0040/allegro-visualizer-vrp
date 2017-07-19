#include "Animation.h"

/// <summary>Constructor method</summary>
Animation::Animation() : m_pCurrentFrame(NULL), m_IsVisible(true)
{

}

/// <summary>Destructor method</summary>
Animation::~Animation()
{
	m_pCurrentFrame=NULL;
	std::map<std::string, Frame*>::iterator pos;
	for(pos=m_frames.begin(); pos!=m_frames.end(); ++pos)
	{
		delete pos->second;
	}

	m_frames.clear();
}

/// <summary>Method that render the image of the game agent</summary>
/// \param[in] buffer the image buffer onto which the image of the character is drawn and displayed using double-buffer technque
/// \param[in] center the position of the character on the 2D screen
/// \param[in] angle the rotation of the sprite image
void Animation::Render(BITMAP* buffer, Point2D center, fixed angle)
{
	if(m_pCurrentFrame!=NULL && m_IsVisible)
	{
		m_pCurrentFrame->Render(buffer, center, angle);
	}
}

/// <summary>Method that set the current image of the sprite for the game agent</summary>
/// \param[in] image_src the path to the image file
void Animation::SetCurrent(std::string image_src)
{
	std::map<std::string, Frame*>::iterator pos=m_frames.find(image_src);
	if(pos!=m_frames.end())
	{
		m_pCurrentFrame=pos->second;
	}
	else
	{
		m_pCurrentFrame=new Frame(image_src);
		m_frames[image_src]=m_pCurrentFrame;
	}
}

/// <summary>Method that set the current image of the sprite for the game agent</summary>
/// \param[in] image_src the path to the image file
/// \param[in] scaled_factor the image scaling factor
void Animation::SetCurrent(std::string image_src, float scaled_factor)
{
	std::map<std::string, Frame*>::iterator pos=m_frames.find(image_src);
	if(pos!=m_frames.end())
	{
		m_pCurrentFrame=pos->second;
	}
	else
	{
		m_pCurrentFrame=new Frame(image_src, scaled_factor);
		m_frames[image_src]=m_pCurrentFrame;
	}
}

/// <summary>Method that set whether the sprite is visible</summary>
/// \param[in] val the boolean flag indicating whether the sprite is visible
void Animation::SetVisible(bool val)
{
	m_IsVisible=val;
}
