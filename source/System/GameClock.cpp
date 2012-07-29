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

#include <algorithm>
#include <MEngine.h>

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

//----------------------------------------
GameClock::GameClock()
{
	m_StartTime = getCurTime();
	m_CurTime = m_StartTime;
	m_Delta = 0;
}
//----------------------------------------
void GameClock::Update()
{
	// get the new time and then work out the delta
	clocktime prevTime = m_CurTime;
	m_CurTime = getCurTime();
	m_Delta = m_CurTime - prevTime;

	// update any attached timers
	for(timerVecIter iTimer = m_Timers.begin(); 
		iTimer != m_Timers.end(); 
		iTimer++)
	{
		(*iTimer)->Update(m_Delta);
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
clocktime GameClock::GetDeltaMs()
{
	return m_Delta;
}