#ifndef __GAME_STATE_SPLASH_H__
#define __GAME_STATE_SPLASH_H__

#include "Game/GameState.h"
#include "System/MessageSystem.h"

class GameStateSplash : public GameState, public Observer
{
public:
  virtual void Enter();
  virtual void Update();
  virtual void Exit();

  virtual void OnMessage(Message message, int param);
};

#endif/*__GAME_STATE_SPLASH_H__*/
