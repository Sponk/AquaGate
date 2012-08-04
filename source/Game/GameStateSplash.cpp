#include "GameStateSplash.h"

#include "AquaGame.h"

#include <stdio.h>

//----------------------------------------
// Messages
//----------------------------------------
REGISTER_MESSAGE(MSG_EXIT_SPLASH);

//----------------------------------------
// Commands
//----------------------------------------
INPUT("SPACE", ExitSplash, return, SendMessage(MSG_EXIT_SPLASH));

//----------------------------------------
// GameStateSplash
//----------------------------------------
void GameStateSplash::Enter()
{
    GetGame()->GetInputManager()->RegisterCommand(&ExitSplash);
    ExitSplash.AttachObserver(this);
    
    GameState::Enter();
}
//----------------------------------------
void GameStateSplash::Update()
{
    GameState::Update();
}
//----------------------------------------
void GameStateSplash::Exit()
{
    GameState::Update();
}
//----------------------------------------
void GameStateSplash::OnMessage(Message message, int param)
{
  if(message == MSG_EXIT_SPLASH)
    Transition(GameState::eStateLobby);
}
