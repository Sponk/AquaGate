/* GameClock.cpp
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

#include "GameClock.h"

#include "Timer.h"
#include "Util/Util.h"

#include <algorithm>
#include <MEngine.h>

//----------------------------------------
bool _invokeZombie(const Method& m)
{
	return m.Time <= 0 || m.Function == 0;
}
int CLOCK_MAIN = Util::Hash("CLOCK_MAIN");
//----------------------------------------
// getCurTime
// quick helper function to lookup tick
// time
//----------------------------------------
clocktime getCurTime()
{
	MEngine* engine = MEngine::getInstance();
	MSystemContext* system = engine->getSystemContext();

	return system->getSystemTick();
}

GameClock::clockMap GameClock::m_Clocks;

//----------------------------------------
GameClock::GameClock()
{
	m_StartTime = getCurTime();
	m_CurTime = m_StartTime;
	m_Delta = 0;
}
//----------------------------------------
void GameClock::_update()
{
	// get the new time and then work out the delta
	clocktime prevTime = m_CurTime;
	m_CurTime = getCurTime();
	m_Delta = (clocktime)(((float)(m_CurTime - prevTime)) * m_Scale);

	// update any attached timers
	for(timerVecIter iTimer = m_Timers.begin(); 
		iTimer != m_Timers.end(); 
		iTimer++)
	{
		(*iTimer)->Update(m_Delta);
	}

	m_Invokes.remove_if(_invokeZombie);
	for(invokeListIter iInvoke = m_Invokes.begin();
		iInvoke != m_Invokes.end();
		iInvoke++)
	{
		iInvoke->Time -= m_Delta;
		if(iInvoke->Time <= 0)
			iInvoke->Function();
	}
}
//----------------------------------------
Timer* GameClock::CreateTimer(int id)
{
	// create a new timer and push it
	// back onto the update list
	Timer* timer = new Timer(id);
	m_Timers.push_back(timer);
	return timer;
}
//----------------------------------------
void GameClock::DestroyTimer(Timer* timer)
{
	// try to find the timer and remove from
	// the update list
	timerVecIter iTimer = std::find(m_Timers.begin(), 
									m_Timers.end(), 
									timer);
	if(iTimer != m_Timers.end())
	{
		m_Timers.erase(iTimer);
	}

	// regardless of whether it was in the
	// list, we need to delete the timer
	delete timer;
}
//----------------------------------------
void GameClock::Invoke(func cb, clocktime t)
{
	Method method = { cb, t };
	m_Invokes.push_back(method);
}
//----------------------------------------
void GameClock::CancelInvoke(func cb)
{
	for(invokeListIter iInvoke = m_Invokes.begin();
		iInvoke != m_Invokes.end();
		iInvoke++)
	{
		if(iInvoke->Function == cb)
		{
			m_Invokes.erase(iInvoke);
			return;
		}
	}
}
//----------------------------------------
clocktime GameClock::GetDeltaMs()
{
	return m_Delta;
}
//----------------------------------------
void GameClock::SetScale(float s)
{
	m_Scale = s;
}
//----------------------------------------
GameClock* GameClock::GetClock(ClockID id)
{
	clockMapIter iClock = m_Clocks.find(id);
	if(iClock != m_Clocks.end())
		return iClock->second;
	return 0;
}
//----------------------------------------
void GameClock::SetClock(GameClock* clock, ClockID id)
{
	m_Clocks[id] = clock;
}
//----------------------------------------
void GameClock::Update()
{
	for(clockMapIter iClock = m_Clocks.begin();
		iClock != m_Clocks.end();
		++iClock)
		iClock->second->_update();
}