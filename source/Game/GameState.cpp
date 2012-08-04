#include "GameState.h"

#include <stdio.h>

//----------------------------------------
// GameState
//----------------------------------------
void GameState::Enter()
{
}
//----------------------------------------
void GameState::Update()
{
}
//----------------------------------------
void GameState::Exit()
{
}
//----------------------------------------
AquaGame* GameState::GetGame()
{
  return (AquaGame*)ExposeStateMachine();
}
