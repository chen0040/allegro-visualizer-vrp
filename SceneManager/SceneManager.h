#ifndef _H_SCENE_MANAGER_H
#define _H_SCENE_MANAGER_H

#include "../allegro_include/allegro.h"
#include "../GameEntity/BaseGameEntity.h"
#include "../Util/Rect2D.h"
#include <string>
#include <map>
#include <vector>
#include <list>

/// <summary>Class that represents the game world of the game engine</summary>
class SceneManager
{
public:
	/// <summary>Method that returns the singleton instance of the class</summary>
	/// <returns>The singleton instance of the class</returns>
	static SceneManager* Instance();
	/// <summary>Destructor method</summary>
	virtual ~SceneManager();

private:
	/// <summary>Private constructor</summary>
	SceneManager();
	/// <summary>Private copy constructor</summary>
	/// \param[in] rhs the object to be copied
	SceneManager(const SceneManager& rhs);
	/// <summary>Private assignment operator</summary>
	/// \param[in] rhs the object to be copied
	SceneManager& operator=(const SceneManager& rhs);

public:
	/// <summary>Method that updates all the game agents in the world when the timer ticks in the game engine</summary>
	/// \param[in] deltaTime the time duration between two consecutive calls to the update method
	void Update(float deltaTime);
	/// <summary>Method taht renders all the game agents in the world</summary>
	/// \param[in] buffer the image buffer onto which the game agents are rendered and displayed using double-buffer techniques
	void Render(BITMAP* buffer);
	/// <summary>Method that initialize the game world</summary>
	/// \param[in] filename the configuration file of the application
	/// <returns>The boolean flag indicating whether the loading and initialization is successful</returns>
	bool Init(std::string filename);

public:
	/// <summary>Method that redraws the translucent panel on the GUI of the game engine</summary>
	void InvalidateTranslucentBackPanel();

private:
	/// <summary>Method that renders the panel that displays routing of the vehicles</summary>
	/// \param[in] buffer the image buffer onto which the panel is rendered and displayed using double-buffer techniques
	void RenderRoutingInfo(BITMAP* buffer);
	/// <summary>Method that renders the panel that displays the vehicle ifo</summary>
	/// \param[in] buffer the image buffer onto which the panel is rendered and displayed using double-buffer technique
	void RenderVehicleInfo(BITMAP* buffer);
	/// <summary>Method that renders the customer id on each customer agent</summary>
	/// \param[in] buffer the image buffer onto which the station ids are rendered and displayed using double-buffer technique
	void RenderStationIds(BITMAP* buffer);
	/// <summary>Method that renders the vehicle id on each vehicle agent</summary>
	/// \param[in] buffer the image buffer onto which the vehicle ids are rendered and displayed using double-buffer technique
	void RenderVehicleIds(BITMAP* buffer);
	/// <summary>Method that handles the key polling events</summary>
	void UpdateKeyStates();

private:
	/// <summary>The image for the backgorund of the routing panel</summary>
	BITMAP* m_RoutingInfoPanelBack;

private:
	/// <summary>The store for the customers</summary>
	std::map<std::string, BaseGameEntity*> m_pStations;
	/// <summary>The store for the depots</summary>
	std::map<std::string, BaseGameEntity*> m_pDepots;

private:
	/// <summary>The store for the vehicles</summary>
	std::vector<BaseGameEntity*> m_pVehicles;
	/// <summary>The store for the currently active vehicles</summary>
	std::list<BaseGameEntity*> m_pActiveVehicles;
public:
	/// <summary>Method that starts the engines of the vehicles</summary>
	void StartVR();

private:
	/// <summary>The colors of the vehicle routes</summary>
	int m_clrs[7];

private:
	/// <summary>the activity region of the game engine</summary>
	Rect2D m_SimulatorActivityZone;
public:
	/// <summary>Method that adjust the boundary of the activity region of the game engine</summary>
	/// \param[in] x the horizontal value to which the boundary of the activtiy region should be extended to
	/// \param[in] y the vertical value to which the boundary of the activity region should be extended to
	void AdjustSimulatorActivityZone(float x, float y);
	/// <summary>Method that returns the activity region of the game engine</summary>
	/// <returns>The activity region of the game engine</returns>
	Rect2D GetSimulatorActivityZone() { return m_SimulatorActivityZone; }

private:
	/// <summary>The animation sequence for the game world itself</summary>
	Animation* m_pAnimation;

private:
	/// <summary>The boolean flag indicating whether the routing info panel should be visible</summary>
	bool m_RoutingInfoVisible;
	/// <summary>The boolean flag indicating whether the vehicle info panel should be visible</summary>
	bool m_VehicleInfoVisible;
	/// <summary>The boolean flag indicating whether the menu should be visible</summary>
	bool m_MenuVisible;
	/// <summary>The boolean flag indicating whether the station id should be visible</summary>
	bool m_StationIdVisible;
	/// <summary>The boolean flag indicating whether the vheicle id should be visible</summary>
	bool m_VehicleIdVisible;
};

#define SimulatorSceneManager SceneManager::Instance()

#endif