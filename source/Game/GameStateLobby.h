#ifndef __GAME_STATE_LOBBY_H__
#define __GAME_STATE_LOBBY_H__

#include "Game/GameState.h"

class GameStateLobby : public GameState
{
public:
  virtual void Enter();
  virtual void Update();
  virtual void Exit();

};

#endif/*__GAME_STATE_LOBBY_H__*/
