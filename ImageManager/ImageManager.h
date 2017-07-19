#ifndef _H_IMAGE_MANAGER_H
#define _H_IMAGE_MANAGER_H

#include <string>
#include <map>
#include "../allegro_include/allegro.h"

/// <summary>Class that represents the image manager of the game engine<summary>
class ImageManager
{
public:
	/// <summary>Method that return the single instance of the class</summary>
	static ImageManager* Instance();
	/// <summary>Destructor method</summary>
	virtual ~ImageManager();

private:
	/// <summary>Private constructor for the singleton class</summary>
	ImageManager();
	/// <summary>Private copy constructor for the singleton class</summary>
	/// \param[in] rhs the object to be copied
	ImageManager(const ImageManager& rhs);
	/// <summary>Private assigment operator for the singleton class</summary>
	/// \param[in] rhs the object to be copied
	ImageManager& operator=(const ImageManager& rhs);

public:
	/// <summary>Method that stores an image</summary>
	/// \param[in] image_id the image id tagged with the image
	/// \param[in] bmp the bitmap image to be stored
	void SetImage(std::string image_id, BITMAP* bmp);
	/// <summary>Method that returns a image using its tag</summary>
	/// \param[in] image_id the image tag
	/// <returns>The bitmap image associated with the image tag</returns>
	BITMAP* GetImage(std::string image_id);
	/// <summary>Method that loads an image from a file</summary>
	/// \param[in] image_src The image file path
	void LoadImageFromFile(std::string image_src);
	/// <summary>Method that create a translucent image from the image file</summary>
	/// \param[in] image_src the image file path
	/// \param[in] width the image width
	/// \param[in] height the image height
	/// \param[in] overwrite the boolean flag indicating whether the image should be overwritten if already exist
	/// <returns>TThe translucent image from the image file</returns>
	BITMAP* CreateTranslucentImageFromFile(std::string image_src, int width, int height,bool overwrite=false);

private:
	/// <summary>The image store</summary>
	std::map<std::string, BITMAP*> m_images;

};

#define SimulatorImageManager ImageManager::Instance()

#endif