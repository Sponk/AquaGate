/* GameClock.h
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

#ifndef __GAME_CLOCK_H__
#define __GAME_CLOCK_H__

#include <vector>

class Timer;

//--------------------------------------------
// typedef's
//--------------------------------------------
typedef long int clocktime;

//--------------------------------------------
// GameClock
//
// Takes care of any active timers, also
// provides an interface for getting the delta
// between ticks
//--------------------------------------------
class GameClock
{
public:
	GameClock();
	
	//----------------------------------------
	// Public interface
	//----------------------------------------
	void	Update();

	Timer*		CreateTimer(int id);
	void		DestroyTimer(Timer* timer);

	clocktime	GetDeltaMs();

private:
	//----------------------------------------
	// Internal types
	//----------------------------------------
	typedef std::vector<Timer*> timerVec;
	typedef timerVec::iterator	timerVecIter;
	
	//----------------------------------------
	// Members
	//----------------------------------------
	timerVec	m_Timers;

	clocktime	m_StartTime;
	clocktime	m_CurTime;
	clocktime	m_Delta;
};

#endif /*__GAME_CLOCK_H__*/