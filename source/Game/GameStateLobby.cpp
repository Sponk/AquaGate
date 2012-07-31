#include "GameStateLobby.h"

#include <stdio.h>

void GameStateLobby::Enter()
{
  printf("Enter Lobby\n");
  GameState::Enter();
}

void GameStateLobby::Update()
{
  printf("Update Lobby\n");
  GameState::Update();
}

void GameStateLobby::Exit()
{
  printf("Exit Lobby\n");
  GameState::Update();
}
