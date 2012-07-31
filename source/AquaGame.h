/* AquaGame.h
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

#ifndef __AQUA_GAME_H__
#define __AQUA_GAME_H__

#include "MEngine.h"

#include "System/Object.h"
#include "System/GameClock.h"
#include "System/MessageSystem.h"
#include "System/InputManager.h"

#include "Graphics/PostProcessor.h"

//--------------------------------------------
// AquaGame
//
// Our friendly neighbourhood game class
// This class should wrap up any game specific
// functionality
//--------------------------------------------
class AquaGame : public MGame, public Subject, public Observer, public Object
{
public:
	AquaGame();
	~AquaGame();
	
	//----------------------------------------
	// MGame virtuals
	//----------------------------------------
	virtual void update();
	virtual void draw();
	
	//----------------------------------------
	// Observer virtuals
	//----------------------------------------
    void OnMessage(Message message, int param);

	//----------------------------------------
	// Public interface
	//----------------------------------------
	GameClock*		GetGameClock();
	MessageSystem*	GetMessageSystem();
	InputManager*	GetInputManager();

private:
	GameClock		m_Clock;

	MessageSystem	m_MessageSystem;

	InputManager	m_InputManager;
	
	PostProcessor   m_PostProcessor;
};

#endif /*__AQUA_GAME_H__*/
