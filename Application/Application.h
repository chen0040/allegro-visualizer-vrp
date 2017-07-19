#ifndef _H_APPLICATION_H
#define _H_APPLICATION_H

#include "../allegro_include/allegro.h"

/// <summary>Class that represents the game engine of the application</summary>
class Application
{
public:
	/// <summary>Singleton method that returns the single instance of this class</summary>
	static Application* Instance();
	/// <summary>Destructor method</summary>
	virtual ~Application();

private:
	/// <summary>Private constructor method</summary>
	Application();
	/// <summary>Private copy constructor</summary>
	/// \param[in] rhs the object to be copied
	Application(const Application& rhs);
	/// <summary>Private assignment operator</summary>
	Application& operator=(const Application & rhs);

public:
	/// <summary>Method that initialize the game engine</summary>
	/// \param[in] width the width of the screen area onto which the animation sprites of game agents are drawn
	/// \param[in] height the height of the screen area onto which the animation sprites of the game characters are drawn
	/// \param[in] windowed the boolean flag indicating whether the game engine should be open in a window mode instead of fullscreen
	bool Init(int width, int height, bool windowed);
	/// <summary>Method that ticks the timer of the game engine, which is called iteratively to update the game world and characters</summary>
	/// \param[in] deltaTime the time interval between the two cnosecutive calls to the update method
	void Update(float deltaTime);
	/// <summary>Method that renders the sprite images of game agents in the game world onto image buffer and displayed using double-buffer techniques</summary>
	/// \param[in] buffer The image buffer onto which the sprite images of characters in the game worlds are rendered and displayed using double-buffer techniques
	void Render(BITMAP* buffer);
	/// <summary>Method that loop iteratively and perform the various operation in the game engine after the game engine is started</summary>
	void Run();
	/// <summary>Method that clean up the memory and resources of the game world, e.g. when the game engine is is shutdown</summary>
	void Cleanup();

private:
	/// <summary>The initial 2D game height of the game world</summary>
	float m_GameHeight;
	/// <summary>The initial 2D game width of the game world</summary>
	float m_GameWidth;
	/// <summary>The 2D game height</summary>
	float m_sh;
	/// <summary>The 2D game width</summary>
	float m_sw;
	/// <summary>The reported 2D screen height</summary>
	float m_ScreenHeight;
	/// <summary>The reported 2D screen width</summary>
	float m_ScreenWidth;
	/// <summary>The left of the 2D game world</summary>
	float m_sLeft;
	/// <summary>The top of the 2D game world</summary>
	float m_sTop;
	/// <summary>The horizontal offset to the left of the 2D screen, actually not in used in the implementation</summary>
	float m_hOffset;
	/// <summary>The vertical offset to the top of the 2D screen, actually not in use in the implementation</summary>
	float m_vOffset;

public:
	/// <summary>Method that returns the height of the 2D game world</summary>
	/// <returns>The height of the 2D game world</returns>
	float GetHeight() { return m_sh; }
	/// <summary>Method that returns the width of the 2D game world</summary>
	/// <returns>The width of the 2D game world</returns>
	float GetWidth() { return m_sw; }
	/// <summary>Method that returns the height of the 2D screen</summary>
	/// <returns>The height of the 2D screen</returns>
	float GetScreenHeight() { return m_ScreenHeight; }
	/// <summary>Method taht returns the width of the 2D screen</summary>
	/// <returns>The width of the 2D screen</returns>
	float GetScreenWidth() { return m_ScreenWidth; }
	/// <summary>Method that returns the current top of the 2D game world</summary>
	/// <returns>The current top of the 2D game world</returns>
	float GetTop() { return m_sTop; }
	/// <summary>Method that returns the current left of the 2D game world</summary>
	/// <returns>The current left of the 2D game world</returns>
	float GetLeft() { return m_sLeft; }
	/// <summary>Method that returns the horizontal offset of hte 2D game world<summary>
	/// <returns>The horizontal offset of the 2D game world</returns>
	float GetHorizontalOffset() { return m_hOffset; }
	/// <summary>Method that returns the vertical offset of the 2D game world</summary>
	/// <returns>The vertical offset of the 2D game world</returns>
	float GetVerticalOffset() { return m_vOffset; }

private:
	/// <summary>The boolean flag indicating whether the game engine is currently running</summary>
	volatile bool m_IsRunning;
public:
	/// <summary>Method that stop the game engine</summary>
	void Stop();
	/// <summary>Method that return the running status of the game engine</summary>
	/// <returns>The boolean flag indicating whether the game engine is currently running</returns>
	bool IsRunning() { return m_IsRunning; }

};

#define SimulatorApp Application::Instance()

#endif