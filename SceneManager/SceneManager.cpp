#include "SceneManager.h"
#include "../tinyxml/tinyxml.h"
#include "../Behavior/Behavior_Station.h"
#include "../Behavior/Behavior_Depot.h"
#include "../Behavior/Behavior_Vehicle.h"
#include "../Profile/Profile_Station.h"
#include "../Profile/Profile_Depot.h"
#include "../Profile/Profile_Vehicle.h"
#include "../ImageManager/ImageManager.h"
#include "../Application/Application.h"
#include "../allegro_include/winalleg.h"
#include <sstream>

/// <summary>Destructor method</summary>
SceneManager::SceneManager() : m_RoutingInfoPanelBack(NULL)
{
	m_clrs[0]=makecol(255, 0, 0);
	m_clrs[1]=makecol(0, 255, 0);
	m_clrs[2]=makecol(0, 0, 255);
	m_clrs[3]=makecol(255, 255, 0);
	m_clrs[4]=makecol(0, 255, 255);
	m_clrs[5]=makecol(255, 0, 255);
	m_clrs[6]=makecol(255, 255, 255);

	m_pAnimation=new Animation();

	SimulatorImageManager->LoadImageFromFile("images\\feul_pipe.bmp");

	m_RoutingInfoVisible=true;
	m_VehicleInfoVisible=true;
	m_MenuVisible=false;
	m_StationIdVisible=true;
	m_VehicleIdVisible=true;
}

/// <summary>Destructor method</summary>
SceneManager::~SceneManager()
{
	std::map<std::string, BaseGameEntity*>::iterator pos1;
	for(pos1=m_pStations.begin(); pos1!=m_pStations.end(); ++pos1)
	{
		delete pos1->second;
	}
	m_pStations.clear();

	for(pos1=m_pDepots.begin(); pos1!=m_pDepots.end(); ++pos1)
	{
		delete pos1->second;
	}
	m_pDepots.clear();

	std::vector<BaseGameEntity*>::iterator pos2;
	for(pos2=m_pVehicles.begin(); pos2!=m_pVehicles.end(); ++pos2)
	{
		delete (*pos2);
	}
	m_pVehicles.clear();
	m_pActiveVehicles.clear();

	if(m_pAnimation!=NULL)
	{
		delete m_pAnimation;
		m_pAnimation=NULL;
	}

	m_RoutingInfoPanelBack=NULL;
}

/// <summary>Private copy constructor</summary>
/// \param[in] rhs the object to be copied
SceneManager::SceneManager(const SceneManager& rhs)
{

}

/// <summary>Private assignment operator</summary>
/// \param[in] rhs the object to be copied
SceneManager& SceneManager::operator=(const SceneManager& rhs)
{
	return *this;
}

/// <summary>Method that returns the singleton instance of the class</summary>
/// <returns>The singleton instance of the class</returns>
SceneManager* SceneManager::Instance()
{
	static SceneManager theInstance;
	return &theInstance;
}

/// <summary>Method that updates all the game agents in the world when the timer ticks in the game engine</summary>
/// \param[in] deltaTime the time duration between two consecutive calls to the update method
void SceneManager::Update(float deltaTime)
{
	UpdateKeyStates();

	std::list<BaseGameEntity*>::iterator pos1=m_pActiveVehicles.begin();
	if(pos1!=m_pActiveVehicles.end())
	{
		while(pos1!=m_pActiveVehicles.end())
		{
			Behavior_Vehicle* pBehavior=dynamic_cast<Behavior_Vehicle*>((*pos1)->GetBehavior());
			if(pBehavior->IsEnded())
			{
				pos1=m_pActiveVehicles.erase(pos1);
				continue;
			}
			(*pos1)->Update(deltaTime);
			++pos1;
		}
	}
	else
	{
		StartVR();
	}
}

/// <summary>Method that starts the engines of the vehicles</summary>
void SceneManager::StartVR()
{
	for(unsigned int i=0; i<m_pVehicles.size(); i++)
	{
		Behavior_Vehicle* pBehavior=dynamic_cast<Behavior_Vehicle*>(m_pVehicles[i]->GetBehavior());
		pBehavior->Start();
		m_pActiveVehicles.push_back(m_pVehicles[i]);
	}
}

/// <summary>Method taht renders all the game agents in the world</summary>
/// \param[in] buffer the image buffer onto which the game agents are rendered and displayed using double-buffer techniques
void SceneManager::Render(BITMAP* buffer)
{
	//std::vector<BaseGameEntity*>::iterator pos2;
	//for(pos2=m_pVehicles.begin(); pos2!=m_pVehicles.end(); ++pos2)
	for(unsigned int i=0; i<m_pVehicles.size(); i++)
	{
		Behavior_Vehicle* pBehavior=dynamic_cast<Behavior_Vehicle*>(m_pVehicles[i]->GetBehavior());
		pBehavior->RenderPath(buffer, m_clrs[i % 7]);
	}

	for(unsigned int i=0; i<m_pVehicles.size(); i++)
	{
		m_pVehicles[i]->Render(buffer);
	}

	if(m_VehicleIdVisible)
	{
		RenderVehicleIds(buffer);
	}

	std::map<std::string, BaseGameEntity*>::iterator pos1;
	for(pos1=m_pStations.begin(); pos1!=m_pStations.end(); ++pos1)
	{
		pos1->second->Render(buffer);
	}

	for(pos1=m_pDepots.begin(); pos1!=m_pDepots.end(); ++pos1)
	{
		pos1->second->Render(buffer);
	}

	if(m_StationIdVisible)
	{
		RenderStationIds(buffer);
	}

	if(m_RoutingInfoVisible)
	{
		RenderRoutingInfo(buffer);
	}
	if(m_VehicleInfoVisible)
	{
		RenderVehicleInfo(buffer);
	}

	if(m_MenuVisible)
	{
		text_mode(-1);
		int mw=20;
		int mh=SimulatorApp->GetScreenHeight()-150;

		textout(buffer, font, "-Press [M] to hide menu", mw, mh, makecol(255, 255, 255));
		textout(buffer, font, "-Press [A] to hide Routing Info Panel", mw, mh+10, makecol(255, 255, 255));
		textout(buffer, font, "-Press [S] to show Routing Info Panel", mw, mh+20, makecol(255, 255, 255));
		textout(buffer, font, "-Press [B] to hide Vehilce Info Panel", mw, mh+30, makecol(255, 255, 255));
		textout(buffer, font, "-Press [V] to show Vehicle Info Panel", mw, mh+40, makecol(255, 255, 255));
		textout(buffer, font, "-Press [Q] to hide station id", mw, mh+50, makecol(255, 255, 255));
		textout(buffer, font, "-Press [W] to show station id", mw, mh+60, makecol(255, 255, 255));
		textout(buffer, font, "-Press [E] to hide vehicle id", mw, mh+70, makecol(255, 255, 255));
		textout(buffer, font, "-Press [R] to show vehicle id", mw, mh+80, makecol(255, 255, 255));
		textout(buffer, font, "-Press [SPACE_BAR] to toggle between fullscreen", mw, mh+90, makecol(255, 255, 255));
	}
	else
	{
		text_mode(-1);
		int mw=20;
		int mh=SimulatorApp->GetScreenHeight()-100;
		textout(buffer, font, "Press [N] to show menu", mw, mh, makecol(255, 255, 255));
	}
}

/// <summary>Method that initialize the game world</summary>
/// \param[in] filename the configuration file of the application
/// <returns>The boolean flag indicating whether the loading and initialization is successful</returns>
bool SceneManager::Init(std::string filename)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str()))
	{
		std::ostringstream oss;
		oss << "Failed to the file " << filename;
		std::string msg=oss.str();
		allegro_message(msg.c_str());

		return false;
	}

	TiXmlElement* pXmlRoot=doc.RootElement();

	for(TiXmlElement* pXmlElement1=pXmlRoot->FirstChildElement(); pXmlElement1!=NULL; pXmlElement1=pXmlElement1->NextSiblingElement())
	{
		if(strcmp(pXmlElement1->Value(), "depots")==0)
		{
			for(TiXmlElement* pXmlElement2=pXmlElement1->FirstChildElement(); pXmlElement2!=NULL; pXmlElement2=pXmlElement2->NextSiblingElement())
			{
				if(strcmp(pXmlElement2->Value(), "station")==0)
				{
					BaseGameEntity* pStation=new BaseGameEntity();
					std::string station_id=pXmlElement2->Attribute("id");

					float x, y;
					pXmlElement2->QueryFloatAttribute("x", &x);
					pXmlElement2->QueryFloatAttribute("y", &y);

					AdjustSimulatorActivityZone(x, y);

					Profile_Depot* pProfile=new Profile_Depot(station_id);
					pStation->SetProfile(pProfile);

					Behavior_Depot* pBehavior=new Behavior_Depot(pStation);
					pBehavior->SetPosition(Point2D(x, y));
					pStation->SetBehavior(pBehavior);

					m_pDepots[station_id]=pStation;
				}
			}
		}
		else if(strcmp(pXmlElement1->Value(), "stations")==0)
		{
			for(TiXmlElement* pXmlElement2=pXmlElement1->FirstChildElement(); pXmlElement2!=NULL; pXmlElement2=pXmlElement2->NextSiblingElement())
			{
				if(strcmp(pXmlElement2->Value(), "station")==0)
				{
					BaseGameEntity* pStation=new BaseGameEntity();
					std::string station_id=pXmlElement2->Attribute("id");

					float x, y, demand;
					pXmlElement2->QueryFloatAttribute("x", &x);
					pXmlElement2->QueryFloatAttribute("y", &y);
					pXmlElement2->QueryFloatAttribute("demand", &demand);

					AdjustSimulatorActivityZone(x, y);

					Profile_Station* pProfile=new Profile_Station(station_id);
					pProfile->SetDemand(demand);
					pStation->SetProfile(pProfile);

					Behavior_Station* pBehavior=new Behavior_Station(pStation);
					pBehavior->SetPosition(Point2D(x, y));
					pBehavior->SetDemand(demand);
					
					pStation->SetBehavior(pBehavior);

					m_pStations[station_id]=pStation;
				}
			}
		}
	}

	/*
	std::ostringstream oss;
	oss << "width: " << m_SimulatorActivityZone.Width();
	std::string msg=oss.str();
	allegro_message(msg.c_str());
	*/
	


	for(TiXmlElement* pXmlElement1=pXmlRoot->FirstChildElement(); pXmlElement1!=NULL; pXmlElement1=pXmlElement1->NextSiblingElement())
	{
		if(strcmp(pXmlElement1->Value(), "routes")==0)
		{
			for(TiXmlElement* pXmlElement2=pXmlElement1->FirstChildElement(); pXmlElement2!=NULL; pXmlElement2=pXmlElement2->NextSiblingElement())
			{
				if(strcmp(pXmlElement2->Value(), "route")==0)
				{
					float capacity=0.0f, speed=0.0f;
					pXmlElement2->QueryFloatAttribute("vehicle_capacity", &capacity);
					pXmlElement2->QueryFloatAttribute("vehicle_speed", &speed);

					BaseGameEntity* pVehicle=new BaseGameEntity();

					std::ostringstream oss;
					oss << "v{" << m_pVehicles.size() << "}";
					std::string vehicle_id=oss.str();

					Profile_Vehicle* pProfile=new Profile_Vehicle(vehicle_id);
			
					Behavior_Vehicle* pBehavior=new Behavior_Vehicle(pVehicle);
					pBehavior->SetSpeed(speed);
					pBehavior->SetCapacity(capacity);

					for(TiXmlElement* pXmlElement3=pXmlElement2->FirstChildElement(); pXmlElement3!=NULL; pXmlElement3=pXmlElement3->NextSiblingElement())
					{
						if(strcmp(pXmlElement3->Value(), "station")==0)
						{
							std::string id=pXmlElement3->Attribute("id");

							BaseGameEntity* pStation=NULL;
							if(m_pStations.find(id)==m_pStations.end())
							{
								pStation=m_pDepots[id];
							}
							else
							{
								pStation=m_pStations[id];
							}
							assert(pStation!=NULL);
							pBehavior->AddStationToVisit(pStation);
						}
					}

					pVehicle->SetProfile(pProfile);
					pVehicle->SetBehavior(pBehavior);

					pVehicle->GetAnimation()->SetVisible(false);

					m_pVehicles.push_back(pVehicle);
				}
			}
		}
	}

	InvalidateTranslucentBackPanel();

	return true;
}

/// <summary>Method that adjust the boundary of the activity region of the game engine</summary>
/// \param[in] x the horizontal value to which the boundary of the activtiy region should be extended to
/// \param[in] y the vertical value to which the boundary of the activity region should be extended to
void SceneManager::AdjustSimulatorActivityZone(float x, float y)
{
	if(m_SimulatorActivityZone.top > y)
	{
		m_SimulatorActivityZone.top=y;
	}
	if(m_SimulatorActivityZone.bottom < y)
	{
		m_SimulatorActivityZone.bottom=y;
	}
	if(m_SimulatorActivityZone.left > x)
	{
		m_SimulatorActivityZone.left=x;
	}
	if(m_SimulatorActivityZone.right < x)
	{
		m_SimulatorActivityZone.right=x;
	}

}

/// <summary>Method that renders the panel that displays routing of the vehicles</summary>
/// \param[in] buffer the image buffer onto which the panel is rendered and displayed using double-buffer techniques
void SceneManager::RenderRoutingInfo(BITMAP* buffer)
{
	const static int item_height=32;
	const static int item_width=32;
	const static int vertical_gap=5;
	const static int vertical_inset=5;
	const static int horizontal_inset=5;

	int height=item_height * m_pVehicles.size() + vertical_gap * (m_pVehicles.size() - 1) + vertical_inset * 2;
	int width=SimulatorApp->GetScreenWidth() * 2 / 5;

	int left=10;
	int top=20;

	set_alpha_blender();
	draw_trans_sprite(buffer, m_RoutingInfoPanelBack, 10, 20);
	rect(buffer, left, top, left+width, top+height, makecol(128, 128, 128));

	for(unsigned int i=0; i<m_pVehicles.size(); i++)
	{
		unsigned int box_top=top+vertical_inset+i * (vertical_gap + item_height);
		unsigned int box_bottom=box_top + item_height;
		unsigned int box_left=left+horizontal_inset;
		unsigned int box_right=box_left+width-horizontal_inset*2;
		rect(buffer, box_left, box_top, box_right, box_bottom, m_clrs[i % 7]);

		Behavior_Vehicle* pBehavior=dynamic_cast<Behavior_Vehicle*>(m_pVehicles[i]->GetBehavior());
		if(pBehavior->IsMoving())
		{
			m_pAnimation->SetCurrent("images\\vehicle_run.bmp", 1.2);
			m_pAnimation->Render(buffer, Point2D(box_left+20, box_top+18), 0);

			m_pAnimation->SetCurrent("images\\vehicle_wheel.bmp", 1.2);
			m_pAnimation->Render(buffer, Point2D(box_left+55, box_top+16), 0);
		}
		else
		{
			m_pAnimation->SetCurrent("images\\vehicle_pause.bmp", 1.2);
			m_pAnimation->Render(buffer, Point2D(box_left+20, box_top+16), 0);

			if(pBehavior->IsEnded())
			{
				m_pAnimation->SetCurrent("images\\vehicle_pause_at_depot.bmp", 1.0);
				m_pAnimation->Render(buffer, Point2D(box_left+55, box_top+16), 0);
			}
			else
			{
				m_pAnimation->SetCurrent("images\\vehicle_pause_at_station.bmp", 1.0);
				m_pAnimation->Render(buffer, Point2D(box_left+55, box_top+16), 0);
			}
		}

		text_mode(-1);
		textout(buffer, font, pBehavior->ToString().c_str(), (box_left+75), (box_top+box_bottom)/2-1, makecol(255, 255, 255));
	}
}

/// <summary>Method that redraws the translucent panel on the GUI of the game engine</summary>
void SceneManager::InvalidateTranslucentBackPanel()
{
	const static int item_height=32;
	const static int item_width=32;
	const static int vertical_gap=5;
	const static int vertical_inset=5;
	const static int horizontal_inset=5;

	int height=item_height * m_pVehicles.size() + vertical_gap * (m_pVehicles.size() - 1) + vertical_inset * 2;
	int width=SimulatorApp->GetWidth() * 2 / 5;

	/*
	std::ostringstream oss;
	oss << "width: " << width << " height: " << height;
	std::string msg=oss.str();

	allegro_message(msg.c_str());
	*/

	m_RoutingInfoPanelBack=SimulatorImageManager->CreateTranslucentImageFromFile("images\\panel_back.bmp", width, height, true);
}

/// <summary>Method that renders the panel that displays the vehicle ifo</summary>
/// \param[in] buffer the image buffer onto which the panel is rendered and displayed using double-buffer technique
void SceneManager::RenderVehicleInfo(BITMAP* buffer)
{
	const static int item_height=32;
	const static int item_width=32;
	const static int vertical_gap=5;
	const static int vertical_inset=5;
	const static int horizontal_inset=5;

	int height=item_height * m_pVehicles.size() + vertical_gap * (m_pVehicles.size() - 1) + vertical_inset * 2;
	int width=SimulatorApp->GetScreenWidth() * 2 / 5;

	int left=SimulatorApp->GetScreenWidth()-width-10;
	int top=20;

	set_alpha_blender();
	draw_trans_sprite(buffer, m_RoutingInfoPanelBack, left, top);
	rect(buffer, left, top, left+width, top+height, makecol(128, 128, 128));

	for(unsigned int i=0; i<m_pVehicles.size(); i++)
	{
		unsigned int box_top=top+vertical_inset+i * (vertical_gap + item_height);
		unsigned int box_bottom=box_top + item_height;
		unsigned int box_left=left+horizontal_inset;
		unsigned int box_right=box_left+width-horizontal_inset*2;
		rect(buffer, box_left, box_top, box_right, box_bottom, m_clrs[i % 7]);

		Behavior_Vehicle* pBehavior=dynamic_cast<Behavior_Vehicle*>(m_pVehicles[i]->GetBehavior());
		if(pBehavior->IsMoving())
		{
			m_pAnimation->SetCurrent("images\\vehicle_run.bmp", 1.2);
			m_pAnimation->Render(buffer, Point2D(box_left+20, box_top+18), 0);
		}
		else
		{
			m_pAnimation->SetCurrent("images\\vehicle_pause.bmp", 1.2);
			m_pAnimation->Render(buffer, Point2D(box_left+20, box_top+18), 0);
		}

		stretch_sprite(buffer, SimulatorImageManager->GetImage("images\\feul_pipe.bmp"), (box_left+80), box_top+item_height*0.15f, (width-110) * pBehavior->GetRemainingLoadInPercentage(), item_height*0.8f);
		text_mode(-1);
		textout(buffer, font, m_pVehicles[i]->GetProfile()->GetID().c_str(), (box_left+40), (box_top+box_bottom)/2-1, makecol(255, 255, 255));
	}

}

/// <summary>Method that handles the key polling events</summary>
void SceneManager::UpdateKeyStates()
{
	if(key[KEY_A])
	{
		if(m_RoutingInfoVisible)
		{
			m_RoutingInfoVisible=false;
		}
	}
	if(key[KEY_S])
	{
		m_RoutingInfoVisible=true;
	}

	if(key[KEY_B])
	{
		if(m_VehicleInfoVisible)
		{
			m_VehicleInfoVisible=false;
		}
	}
	if(key[KEY_V])
	{
		m_VehicleInfoVisible=true;
	}

	if(key[KEY_M])
	{
		if(m_MenuVisible)
		{
			m_MenuVisible=false;
		}
	}
	if(key[KEY_N])
	{
		m_MenuVisible=true;
	}

	if(key[KEY_Q])
	{
		m_StationIdVisible=false;
	}
	if(key[KEY_W])
	{
		m_StationIdVisible=true;
	}

	if(key[KEY_E])
	{
		m_VehicleIdVisible=false;
	}
	if(key[KEY_R])
	{
		m_VehicleIdVisible=true;
	}

	if(key[KEY_O])
	{
		//ShellExecute(NULL, TEXT("open"), TEXT("results_gui.xml"), NULL, NULL, SW_SHOWNORMAL);
	}
}

/// <summary>Method that renders the customer id on each customer agent</summary>
/// \param[in] buffer the image buffer onto which the station ids are rendered and displayed using double-buffer technique
void SceneManager::RenderStationIds(BITMAP* buffer)
{
	std::map<std::string, BaseGameEntity*>::iterator pos1;

	for(pos1=m_pStations.begin(); pos1!=m_pStations.end(); ++pos1)
	{
		BaseGameEntity* pStation=pos1->second;
		Point2D position=pStation->GetScreenPosition();
		text_mode(-1);
		textout(buffer, font, pStation->GetProfile()->GetID().c_str(), position.GetX(), position.GetY()-20, makecol(255, 255, 255));
	}

	for(pos1=m_pDepots.begin(); pos1!=m_pDepots.end(); ++pos1)
	{
		BaseGameEntity* pStation=pos1->second;
		Point2D position=pStation->GetScreenPosition();
		text_mode(-1);
		textout(buffer, font, pStation->GetProfile()->GetID().c_str(), position.GetX(), position.GetY()-20, makecol(255, 255, 255));
	}
}

/// <summary>Method that renders the vehicle id on each vehicle agent</summary>
/// \param[in] buffer the image buffer onto which the vehicle ids are rendered and displayed using double-buffer technique
void SceneManager::RenderVehicleIds(BITMAP* buffer)
{
	std::list<BaseGameEntity*>::iterator pos1=m_pActiveVehicles.begin();
	while(pos1!=m_pActiveVehicles.end())
	{
		BaseGameEntity* pV=*pos1;
		
		Point2D position=pV->GetScreenPosition();
		text_mode(-1);
		textout(buffer, font, pV->GetProfile()->GetID().c_str(), position.GetX(), position.GetY()-20, makecol(255, 255, 255));

		++pos1;
	}
}
