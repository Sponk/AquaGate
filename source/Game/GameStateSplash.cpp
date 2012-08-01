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

void GameStateSplash::Enter()
{
    GetGame()->GetInputManager()->RegisterCommand(&ExitSplash);
    ExitSplash.AttachObserver(this);

    printf("Enter Splash\n");
    GameState::Enter();
}

void GameStateSplash::Update()
{
    printf("Update Splash\n");
    GameState::Update();
}

void GameStateSplash::Exit()
{
    printf("Exit Splash\n");
    GameState::Update();
}

void GameStateSplash::OnMessage(Message message, int param)
{
  if(message == MSG_EXIT_SPLASH)
    Transition(GameState::eStateLobby);
}
