/* Timer.h
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

#ifndef __TIMER_H__
#define __TIMER_H__

#include "GameClock.h"

//--------------------------------------------
// ITimerAction
//
// Command pattern. Timer callback.
//--------------------------------------------
class ITimerAction
{
public:
	virtual void OnTimerComplete(int id) = 0;
};

#include <vector>

//--------------------------------------------
// Timer
//
// Class to count down to an event.
//--------------------------------------------
class Timer
{
public:
	Timer(int id);

	//----------------------------------------
	// Public interface
	//----------------------------------------
	// Start/stop the timer. Won't affect
	// the time remaining
	void		Start();
	void		Stop();

	// Check whether the timer is still running.
	// Can be not running but not expired.
	bool		IsRunning();

	void		SetTimeMs(clocktime ms);
	clocktime	GetTimeRemaining();
	bool		HasExpired();

	// Action interface
	void AddAction(ITimerAction* action);
	void RemoveAction(ITimerAction* action);
	
	void		Update(clocktime dt);
private:
	// internal types
	typedef std::vector<ITimerAction*>	actionVec;
	typedef actionVec::iterator			actionVecIter;

	actionVec	m_Actions;

	clocktime	m_TimeMs;
	bool		m_IsRunning;

	// every Timer used by a class should have a
	// different ID. It's only used for letting
	// the action know which timer has expired
	// so there's no need for the id to be
	// unique across the whole system.
	int			m_ID;
};

#endif /*__TIMER_H__*/