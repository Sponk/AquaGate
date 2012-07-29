/* PenguinController.cpp
  version 0.0.1, February 12th, 2012

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

#include "PenguinController.h"

#include "AquaGame.h"
#include "System/InputManager.h"

REGISTER_BEHAVIOUR(PenguinController);
//----------------------------------------
// Messages
//----------------------------------------

//----------------------------------------
// quick defines
//----------------------------------------

//----------------------------------------
// PenguinController
//----------------------------------------
PenguinController::PenguinController(MObject3d * parentObject)
:Behaviour(parentObject, GetStaticID())
{
}
//----------------------------------------
PenguinController::PenguinController(PenguinController & behavior, 
							MObject3d * parentObject)
:Behaviour(parentObject, GetStaticID())
{
}
//----------------------------------------
PenguinController::~PenguinController(void)
{
	MEngine* engine = MEngine::getInstance();
	if(MGame* game = engine->getGame())
	{
		AquaGame* aquaGame = (AquaGame*)game;
		aquaGame->DetachObserver(this);
	}
}
//----------------------------------------
void PenguinController::destroy()
{
	delete this;
}
//----------------------------------------
MBehavior* PenguinController::getNew(MObject3d* parentObject)
{
	return new PenguinController(parentObject);
}
//----------------------------------------
MBehavior* PenguinController::getCopy(MObject3d* parentObject)
{
	return new PenguinController(*this, parentObject);
}
//----------------------------------------
void PenguinController::update()
{
	// just a check to see if the behaviour manager is working right
	if(GetBehaviour<PenguinController>() != this)
		return;
}
//----------------------------------------
void PenguinController::OnMessage(Message message, int param1)
{
}
