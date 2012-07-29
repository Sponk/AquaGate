/* Timer.cpp
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

#include "Timer.h"

#include <algorithm>

//----------------------------------------
// Timer
//----------------------------------------
Timer::Timer(int id)
:m_ID(id)
,m_IsRunning(true)
,m_TimeMs(0)
{
}
//----------------------------------------
void Timer::Start()
{
	m_IsRunning = true;
}
//----------------------------------------
void Timer::Stop()
{
	m_IsRunning = false;
}
//----------------------------------------
bool Timer::IsRunning()
{
	return m_IsRunning;
}
//----------------------------------------
void Timer::Update(clocktime dt)
{
	if(m_IsRunning && m_TimeMs > 0)
	{
		// tick the timer
		m_TimeMs -= dt;

		// check if we've expired
		if(m_TimeMs < 0)
		{
			// make sure the timer doesn't
			// get below 0
			m_TimeMs = 0;

			// let any attached actions know
			actionVecIter iAction;
			for(iAction = m_Actions.begin();
				iAction != m_Actions.end();
				iAction++)
			{
				(*iAction)->OnTimerComplete(m_ID);
			}
			m_IsRunning = false;
		}
	}
}
//----------------------------------------
void Timer::SetTimeMs(clocktime ms)
{
	m_TimeMs = ms;
}
//----------------------------------------
clocktime Timer::GetTimeRemaining()
{
	return m_TimeMs;
}
//----------------------------------------
bool Timer::HasExpired()
{
	return m_TimeMs <= 0;
}
//----------------------------------------
void Timer::AddAction(ITimerAction* action)
{
	// make sure that we haven't already
	// added this action, otherwise we
	// would get OnTimerComplete called
	// multiple times
	if(std::find(	m_Actions.begin(),
					m_Actions.end(), 
					action) == m_Actions.end())
	{
		m_Actions.push_back(action);
	}
}
//----------------------------------------
void Timer::RemoveAction(ITimerAction* action)
{
	// lookup the action and remove
	actionVecIter iAction = 
		std::find(	m_Actions.begin(),
					m_Actions.end(), 
					action);
	if(iAction != m_Actions.end())
	{
		m_Actions.erase(iAction);
	}
}