#include "ImageManager.h"
#include <cassert>

/// <summary>Destructor method</summary>
ImageManager::ImageManager()
{

}

/// <summary>Destructor method</summary>
ImageManager::~ImageManager()
{
	std::map<std::string, BITMAP*>::iterator pos;
	for(pos=m_images.begin(); pos!=m_images.end(); ++pos)
	{
		destroy_bitmap(pos->second);
	}
	m_images.clear();
}

/// <summary>Private assigment operator for the singleton class</summary>
/// \param[in] rhs the object to be copied
ImageManager& ImageManager::operator=(const ImageManager& rhs)
{
	return *this;
}

/// <summary>Private copy constructor for the singleton class</summary>
/// \param[in] rhs the object to be copied
ImageManager::ImageManager(const ImageManager& rhs)
{

}

/// <summary>Method that return the single instance of the class</summary>
ImageManager* ImageManager::Instance()
{
	static ImageManager theInstance;
	return &theInstance;
}

/// <summary>Method that stores an image</summary>
/// \param[in] image_id the image id tagged with the image
/// \param[in] bmp the bitmap image to be stored
void ImageManager::SetImage(std::string image_id, BITMAP* bmp)
{
	assert(m_images.find(image_id)==m_images.end());
	
	m_images[image_id]=bmp;
}

/// <summary>Method that returns a image using its tag</summary>
/// \param[in] image_id the image tag
/// <returns>The bitmap image associated with the image tag</returns>
BITMAP* ImageManager::GetImage(std::string image_id)
{
	std::map<std::string, BITMAP*>::iterator pos=m_images.find(image_id);

	assert(pos!=m_images.end());

	return pos->second;
}

/// <summary>Method that loads an image from a file</summary>
/// \param[in] image_src The image file path
void ImageManager::LoadImageFromFile(std::string image_src)
{
	if(m_images.find(image_src)==m_images.end())
	{
		BITMAP* bmp=load_bitmap(image_src.c_str(), NULL);
		SetImage(image_src, bmp);
	}
}

BITMAP* ImageManager::CreateTranslucentImageFromFile(std::string image_src, int width, int height, bool overwrite)
{
	std::map<std::string, BITMAP*>::iterator pos_bmp=m_images.find(image_src);
	if(overwrite==false)
	{
		assert(pos_bmp==m_images.end());
	}
	else
	{
		if(pos_bmp!=m_images.end())
		{
			destroy_bitmap(pos_bmp->second);
			m_images.erase(pos_bmp);
		}
	}
	
	BITMAP* alpha_image=create_bitmap(width, height);
	BITMAP* buffer=create_bitmap(width, height);
	
	BITMAP* orig_image=load_bitmap(image_src.c_str(), NULL);
	stretch_sprite(buffer, orig_image, 0, 0, width, height);
	destroy_bitmap(orig_image);

	drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
	set_write_alpha_blender();
	int a, c;
	for(int x=0; x<buffer->w; ++x)
	{
		for(int y=0; y<buffer->h; ++y)
		{
			c=getpixel(buffer, x, y);
			a=getr(c)+getg(c)+getb(c);
			a=MID(0, a/2-128, 255);
			putpixel(alpha_image, x, y, a);
		}
	}

	drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

	destroy_bitmap(buffer);

	SetImage(image_src, alpha_image);	

	return alpha_image;
}
