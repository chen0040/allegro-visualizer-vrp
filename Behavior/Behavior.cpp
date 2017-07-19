#include "Behavior.h"
#include "../GameEntity/BaseGameEntity.h"

/// <summary>Constructor method</summary>
/// \param[in] pOwner the game agent that express the behavior
Behavior::Behavior(BaseGameEntity* pOwner) : m_pOwner(pOwner), m_speed(0), m_angle(0)
{

}

/// <summary>Destructor method</summary>
Behavior::~Behavior()
{

}


