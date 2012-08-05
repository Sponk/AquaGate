/* TriggerBehaviour.cpp
  version 0.0.2, August 2st, 2012

  Copyright (C) 2012 Philipp Geyer

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Philipp Geyer
*/

/* Changelog
   0.0.2 - 01.08.2012 - Renamed to TriggerBehaviour. Added state machine
                        skeleton to handle controlling the player. - PG
   0.0.1 - 12.02.2012 - Implemented as TuturialBehaviour for 
                        http://nistur.com - PG
*/

#include "TriggerBehaviour.h"

#include <MEngine.h>

REGISTER_BEHAVIOUR(TriggerBehaviour);
//----------------------------------------
// Messages
//----------------------------------------
REGISTER_MESSAGE(MSG_TRIGGER_ENTER);
REGISTER_MESSAGE(MSG_TRIGGER_EXIT);

//----------------------------------------
// quick defines
//----------------------------------------

//----------------------------------------
// TriggerBehaviour
//----------------------------------------
TriggerBehaviour::TriggerBehaviour(MObject3d * parentObject)
    : Behaviour(parentObject, GetStaticID())
    , m_physicsObject(0)
{
    Init();
}
//----------------------------------------
TriggerBehaviour::TriggerBehaviour(TriggerBehaviour & behavior, 
				   MObject3d * parentObject)
    : Behaviour(parentObject, GetStaticID())
    , m_physicsObject(0)
{
    Init();
}
//----------------------------------------
TriggerBehaviour::~TriggerBehaviour(void)
{
}
//----------------------------------------
void TriggerBehaviour::Update()
{
    m_flags.Parse();
    if(m_physicsObject)
    {
	MPhysicsContext* physics = MEngine::getInstance()->getPhysicsContext();
	if(physics->isObjectInCollision(m_physicsObject->getCollisionObjectId()) > 0)
	    printf("Testing\n");
    }
    
}
//----------------------------------------
void TriggerBehaviour::Init()
{
    RegisterVariable(MVariable("Flags", &m_flags.m_flagString, M_VARIABLE_STRING));
    MObject3d* obj = getParentObject();
    if(obj && obj->getType() == M_OBJECT3D_ENTITY)
	m_physicsObject = ((MOEntity*)obj)->getPhysicsProperties();
}
