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
#include "System/MessageSystem.h"
#include "Util/Util.h"

#include <MEngine.h>
#include <algorithm>

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
    , m_signal("...")
{
    Init();
}
//----------------------------------------
TriggerBehaviour::TriggerBehaviour(TriggerBehaviour & behavior, 
    MObject3d * parentObject)
    : Behaviour(parentObject, GetStaticID())
    , m_physicsObject(0)
    , m_signal("...")
{
    Init();
}
//----------------------------------------
TriggerBehaviour::~TriggerBehaviour(void)
{
}
//----------------------------------------
#ifndef MAX_COLLISION
# define MAX_COLLISION 10
#endif
void TriggerBehaviour::Update()
{
    static unsigned int collisionList[MAX_COLLISION];
    static objectSet    collisionSet;

    unsigned int signal = Util::Hash(m_signal.getData());

    collisionSet.clear();
    if(m_physicsObject)
    {
        MPhysicsContext* physics = MEngine::getInstance()->getPhysicsContext();
        int numCollisions = physics->isObjectInCollision(m_physicsObject->getCollisionObjectId(), collisionList, MAX_COLLISION);

        for(int i=0; i<MIN(numCollisions, MAX_COLLISION); ++i)
            collisionSet.push_back((MObject3d*)physics->getObjectUserPointer(collisionList[i]));
    }

    if(collisionSet.size() > 0)
    {
        for(objectSetIter iObj = collisionSet.begin(); iObj != collisionSet.end(); ++iObj)
        {
            if(std::find(m_contents.begin(), m_contents.end(), *iObj) == m_contents.end())
            {
                m_contents.push_back(*iObj);
                Broadcaster::Broadcast(*iObj, MSG_TRIGGER_ENTER, signal);
                CallScript("onTriggerEnter", *iObj, m_signal.getData());
            }
        }
    }

    if(m_contents.size() > 0)
    {
        for(unsigned int i = 0; i < m_contents.size(); )
        {
            MObject3d* pObj = m_contents[i];
            if(std::find(collisionSet.begin(), collisionSet.end(), pObj) == collisionSet.end())
            {
                Broadcaster::Broadcast(pObj, MSG_TRIGGER_EXIT, signal);
                CallScript("onTriggerExit", pObj, m_signal.getData());

                m_contents.erase(std::find(m_contents.begin(), m_contents.end(), pObj));
                continue;
            }
            ++i;
        }
    }
}
//----------------------------------------
void TriggerBehaviour::Start()
{
    m_flags.Parse();
}
//----------------------------------------
void TriggerBehaviour::Init()
{
    RegisterVariable(MVariable("Flags", &m_flags.m_flagString, M_VARIABLE_STRING));
    RegisterVariable(MVariable("Signal", &m_signal, M_VARIABLE_STRING));

    MObject3d* obj = getParentObject();
    if(obj && obj->getType() == M_OBJECT3D_ENTITY)
        m_physicsObject = ((MOEntity*)obj)->getPhysicsProperties();
}
//----------------------------------------
void TriggerBehaviour::CallScript(const char* function, MObject3d* obj, const char* signal)
{
    MEngine* engine = MEngine::getInstance();
    if(MScriptContext* script = engine->getScriptContext())
    {
        script->pushInteger((int)obj);
        script->pushString(signal);
        script->callFunction(function);
    }
}
