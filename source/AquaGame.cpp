/* AquaGame.cpp
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

#include "AquaGame.h"
#include "System/Timer.h"

#include "Game/GameStateSplash.h"
#include "Game/GameStateLobby.h"

//----------------------------------------
// Messages
//----------------------------------------
REGISTER_MESSAGE(MSG_RELOAD_SHADER);

//----------------------------------------
// Commands
//----------------------------------------
INPUT("R", ReloadShaders, return, SendMessage(MSG_RELOAD_SHADER));

//----------------------------------------
// AquaGame
//----------------------------------------
AquaGame::AquaGame()
: MGame()
, Object("Game")
{
    m_InputManager.RegisterCommand(&ReloadShaders);
    ReloadShaders.AttachObserver(this);
    m_PostProcessor.SetShader(new Shader("shaders/postProcessor.vert","shaders/postProcessor.frag"));
    GameClock::SetClock(&m_Clock, CLOCK_MAIN);

    m_GameStates.AddState(new GameStateSplash(), GameState::eStateSplash);
    m_GameStates.AddState(new GameStateLobby(), GameState::eStateLobby);
    
    m_GameStates.Transition(GameState::eStateSplash);
}
//----------------------------------------
AquaGame::~AquaGame()
{
    delete m_PostProcessor.GetShader();
}
//----------------------------------------
void AquaGame::update()
{
	// tick the game clock
	GameClock::Update();

	m_InputManager.Update();
	
	m_GameStates.Update();
	
	MGame::update();
}
//----------------------------------------
void AquaGame::draw()
{
  if(!m_PostProcessor.Render())
		MGame::draw();
}
//----------------------------------------
void AquaGame::OnMessage(Message message, int param)
{
    if(message == MSG_RELOAD_SHADER)
    {
        delete m_PostProcessor.GetShader();
        m_PostProcessor.SetShader(new Shader("shaders/postProcessor.vert","shaders/postProcessor.frag"));
    }
}
//----------------------------------------
GameClock* AquaGame::GetGameClock()
{
	return &m_Clock;
}
//----------------------------------------
MessageSystem* AquaGame::GetMessageSystem()
{
	return &m_MessageSystem;
}
//----------------------------------------
InputManager* AquaGame::GetInputManager()
{
	return &m_InputManager;
}
