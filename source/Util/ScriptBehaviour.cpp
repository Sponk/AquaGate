/* ScriptBehaviour.cpp
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
   0.0.2 - 01.08.2012 - Renamed to ScriptBehaviour. Added state machine
                        skeleton to handle controlling the player. - PG
   0.0.1 - 12.02.2012 - Implemented as TuturialBehaviour for 
                        http://nistur.com - PG
*/

#include "ScriptBehaviour.h"

#include <MEngine.h>

REGISTER_BEHAVIOUR(ScriptBehaviour);
//----------------------------------------
// Messages
//----------------------------------------

//----------------------------------------
// quick defines
//----------------------------------------

//----------------------------------------
// ScriptBehaviour
//----------------------------------------
ScriptBehaviour::ScriptBehaviour(MObject3d * parentObject)
: Behaviour(parentObject, GetStaticID())
, m_FunctionName("")
{
    Init();
}
//----------------------------------------
ScriptBehaviour::ScriptBehaviour(ScriptBehaviour & behavior, 
							MObject3d * parentObject)
: Behaviour(parentObject, GetStaticID())
, m_FunctionName(behavior.m_FunctionName)
{
    Init();
}
//----------------------------------------
ScriptBehaviour::~ScriptBehaviour(void)
{
}
//----------------------------------------
void ScriptBehaviour::Init()
{
    RegisterVariable(MVariable("Function", &m_FunctionName, M_VARIABLE_STRING));
}
//----------------------------------------
void ScriptBehaviour::destroy()
{
	delete this;
}
//----------------------------------------
MBehavior* ScriptBehaviour::getNew(MObject3d* parentObject)
{
	return new ScriptBehaviour(parentObject);
}
//----------------------------------------
MBehavior* ScriptBehaviour::getCopy(MObject3d* parentObject)
{
	return new ScriptBehaviour(*this, parentObject);
}
//----------------------------------------
void ScriptBehaviour::update()
{
    MEngine* engine = MEngine::getInstance();
    MGame* game = engine->getGame();
    
    if(game == 0 || !game->isRunning())
	return;

    MScriptContext* script = engine->getScriptContext();
    MScene* scene = engine->getLevel()->getCurrentScene();

    unsigned int id;
    scene->getObjectIndex(getParentObject()->getName(), &id);

    script->pushInteger(id);
    script->callFunction(m_FunctionName.getData());
}
//----------------------------------------
void ScriptBehaviour::OnMessage(Message message, int param1)
{
}
