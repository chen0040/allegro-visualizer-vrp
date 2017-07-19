#include "Application.h"
#include "../allegro_include/winalleg.h"
#include "../ImageManager/ImageManager.h"
#include "../SceneManager/SceneManager.h"

/// <summary>Destructor method</summary>
Application::Application() : m_GameWidth(0), m_GameHeight(0), m_IsRunning(false), m_sLeft(0), m_sTop(0), m_vOffset(25), m_hOffset(25)
{

}

/// <summary>Destructor method</summary>
Application::~Application()
{

}

/// <summary>Private copy constructor</summary>
/// \param[in] rhs the object to be copied
Application::Application(const Application& rhs)
{

}

/// <summary>Private assignment operator</summary>
Application& Application::operator=(const Application& rhs)
{
	return *this;
}

/// <summary>Singleton method that returns the single instance of this class</summary>
Application* Application::Instance()
{
	static Application theInstance;
	return &theInstance;
}

/// <summary>Method that ticks the timer of the game engine, which is called iteratively to update the game world and characters</summary>
/// \param[in] deltaTime the time interval between the two cnosecutive calls to the update method
void Application::Update(float deltaTime)
{
	if(key[KEY_ESC])
	{
		Stop();
		return;
	}

	float scale_rate=0.5;

	if(key[KEY_PLUS_PAD])
	{
		m_sw=m_sw+m_sw * scale_rate * deltaTime;
		m_sh=m_sh+m_sh * scale_rate * deltaTime;
	}
	if(key[KEY_MINUS_PAD])
	{
		if(m_sw >= m_ScreenWidth)
		{
			m_sw=m_sw-m_sw * scale_rate * deltaTime;
			m_sh=m_sh-m_sh * scale_rate * deltaTime;
		}
	}

	float scroll_speed=200;

	if(key[KEY_LEFT])
	{
		if(m_sLeft < 0)
		{
			m_sLeft+=scroll_speed * deltaTime;
		}
	}
	if(key[KEY_RIGHT])
	{
		if(m_sLeft+m_sw > m_ScreenWidth)
		{
			m_sLeft-=scroll_speed * deltaTime;
		}
	}
	if(key[KEY_DOWN])
	{
		if(m_sTop+m_sh > m_ScreenHeight)
		{
			m_sTop-=scroll_speed * deltaTime;
		}
	}
	if(key[KEY_UP])
	{
		if(m_sTop < 0)
		{
			m_sTop+=scroll_speed * deltaTime;
		}
	}

	SimulatorSceneManager->Update(deltaTime);
}

/// <summary>Method that stop the game engine</summary>
void Application::Stop()
{
	m_IsRunning=false;
}

/// <summary>Method that loop iteratively and perform the various operation in the game engine after the game engine is started</summary>
void Application::Run()
{
	BITMAP* buffer=create_bitmap(m_GameWidth, m_GameHeight);

	DWORD start_time=timeGetTime();

	int desktop_width, desktop_height;
	get_desktop_resolution(&desktop_width, &desktop_height);

	m_sw=m_GameWidth;
	m_sh=m_GameHeight;

	m_ScreenWidth=m_sw;
	m_ScreenHeight=m_sh;

	m_sLeft=0;
	m_sTop=0;

	bool fullscreen=false;

	while(m_IsRunning)
	{
		if(key[KEY_SPACE])
		{
			if(fullscreen)
			{
				fullscreen=false;
			}
			else
			{
				fullscreen=true;
			}

			if(fullscreen)
			{
				set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, desktop_width, desktop_height, 0, 0);
				m_sLeft=0;
				m_sTop=0;
				m_ScreenWidth=desktop_width;
				m_ScreenHeight=desktop_height;
				m_sw=desktop_width;
				m_sh=desktop_height;
			}
			else
			{
				set_gfx_mode(GFX_AUTODETECT_WINDOWED, m_GameWidth, m_GameHeight, 0, 0);
				m_sLeft=0;
				m_sTop=0;
				m_ScreenWidth=m_GameWidth;
				m_ScreenHeight=m_GameHeight;
				m_sw=m_GameWidth;
				m_sh=m_GameHeight;
			}

			destroy_bitmap(buffer);
			buffer=create_bitmap(m_sw, m_sh);

			SimulatorSceneManager->InvalidateTranslucentBackPanel();
		}

		DWORD end_time=timeGetTime();
		float deltaTime=(end_time-start_time) * 0.001f;

		Update(deltaTime);

		start_time=end_time;

		if(m_IsRunning)
		{
			clear_bitmap(buffer);

			Render(buffer);

			acquire_screen();
			blit(buffer, screen, 0, 0, 0, 0, m_sw, m_sh);
			release_screen();
		}
	}

	destroy_bitmap(buffer);
}

/// <summary>Method that renders the sprite images of game agents in the game world onto image buffer and displayed using double-buffer techniques</summary>
/// \param[in] buffer The image buffer onto which the sprite images of characters in the game worlds are rendered and displayed using double-buffer techniques
void Application::Render(BITMAP* buffer)
{
	BITMAP* bmp=SimulatorImageManager->GetImage("images\\background.bmp");
	stretch_blit(bmp, buffer, 0, 0, bmp->w, bmp->h, m_sLeft, m_sTop, m_sw, m_sh);
	
	bmp=SimulatorImageManager->GetImage("images\\panel_background.bmp");
	stretch_blit(bmp, buffer, 0, 0, bmp->w, bmp->h, 10+m_sLeft, 10+m_sTop, m_sw-20, m_sh-20);

	SimulatorSceneManager->Render(buffer);
}

/// <summary>Method that clean up the memory and resources of the game world, e.g. when the game engine is is shutdown</summary>
void Application::Cleanup()
{

}

/// <summary>Method that initialize the game engine</summary>
/// \param[in] width the width of the screen area onto which the animation sprites of game agents are drawn
/// \param[in] height the height of the screen area onto which the animation sprites of the game characters are drawn
/// \param[in] windowed the boolean flag indicating whether the game engine should be open in a window mode instead of fullscreen
bool Application::Init(int width, int height, bool windowed)
{	
	allegro_init();

	install_keyboard();

	m_GameWidth=width;
	m_GameHeight=height;

	m_sw=width;
	m_sh=height;

	m_ScreenWidth=m_sw;
	m_ScreenHeight=m_sh;

	m_sLeft=0;
	m_sTop=0;

	set_color_depth(32);

	if(windowed)
	{
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	}
	else
	{
		set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, width, height, 0, 0);
	}

	m_IsRunning=true;

	SimulatorImageManager->LoadImageFromFile("images\\panel_background.bmp");
	SimulatorImageManager->LoadImageFromFile("images\\background.bmp");

	SimulatorSceneManager->Init("results_gui.xml");

	return true;
}
