/* PlayerController.cpp
  version 0.0.2, August 1st, 2012

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
   0.0.2 - 01.08.2012 - Renamed to PlayerController. Added state machine
                        skeleton to handle controlling the player. - PG
   0.0.1 - 12.02.2012 - Implemented as TuturialBehaviour for 
                        http://nistur.com - PG
*/

#include "PlayerController.h"

#include "AquaGame.h"
#include "System/InputManager.h"

#include "PlayerControllerStateIdle.h"

REGISTER_BEHAVIOUR(PlayerController);
//----------------------------------------
// Messages
//----------------------------------------

//----------------------------------------
// quick defines
//----------------------------------------

//----------------------------------------
// PlayerController
//----------------------------------------
PlayerController::PlayerController(MObject3d * parentObject)
:Behaviour(parentObject, GetStaticID())
{
  AddState(new PlayerControllerStateIdle(), PlayerControllerState::eStateIdle);

  Transition(PlayerControllerState::eStateIdle);
}
//----------------------------------------
PlayerController::PlayerController(PlayerController & behavior, 
							MObject3d * parentObject)
:Behaviour(parentObject, GetStaticID())
{
}
//----------------------------------------
PlayerController::~PlayerController(void)
{
	MEngine* engine = MEngine::getInstance();
	if(MGame* game = engine->getGame())
	{
		AquaGame* aquaGame = (AquaGame*)game;
		aquaGame->DetachObserver(this);
	}
}
//----------------------------------------
void PlayerController::destroy()
{
	delete this;
}
//----------------------------------------
MBehavior* PlayerController::getNew(MObject3d* parentObject)
{
	return new PlayerController(parentObject);
}
//----------------------------------------
MBehavior* PlayerController::getCopy(MObject3d* parentObject)
{
	return new PlayerController(*this, parentObject);
}
//----------------------------------------
void PlayerController::update()
{
  UpdateStateMachine();
}
//----------------------------------------
void PlayerController::OnMessage(Message message, int param1)
{
}
