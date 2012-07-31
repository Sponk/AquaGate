#include "Util/StateMachine.h"


void StateMachine::AddState(State* state, int id)
{
  state->SetStateMachine(this);
  m_States[id] = state;
}

void StateMachine::Update()
{
  if(m_NextState)
  {
    if(m_CurrentState)
      m_CurrentState->Exit();
    m_CurrentState = m_NextState;
    m_NextState= 0;
    if(m_CurrentState)
      m_CurrentState->Enter();
  }
  else if(m_CurrentState)
    m_CurrentState->Update();
}

void StateMachine::Transition(int id)
{
  stateMapIter iState = m_States.find(id);

  if(iState != m_States.end())
  {
    m_NextState = iState->second;
  }
}
