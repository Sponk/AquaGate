#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include "Util/StateMachine.h"
#include "AquaGame.h"

class GameState : public StateMachine::State
{
public:
  virtual void Enter();
  virtual void Update();
  virtual void Exit();

  enum
  {
    eStateSplash,
    eStateLobby,
    eStateGame,
  };

protected:
  AquaGame* GetGame();
};

#endif/*__GAMESTATE_H__*/
