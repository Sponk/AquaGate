/* GameClock.h
  version 0.0.2, February 12th, 2012

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
#include <list>
#include <map>

#include "System/Object.h"

class Timer;

//--------------------------------------------
// typedef's
//--------------------------------------------
typedef long int clocktime;

typedef void(*func)(void);
typedef void(Object::*method)(void);

typedef unsigned int ClockID;

class _Invoke
{
public:
    _Invoke(clocktime t)
    : _time(t) {}
    void Tick(clocktime dt)
    {
	_time -= dt;
	if(_time <= 0)
	    Invoke();
    }
    virtual void Invoke() = 0;
    virtual bool Zombie() const { return _time <= 0; }
    virtual bool Is(const char* type) = 0;
private:
    clocktime _time;
};

extern int CLOCK_MAIN;
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
	Timer*		CreateTimer(int id);
	void		DestroyTimer(Timer* timer);

	void		Invoke(func cb, clocktime t);
	void		CancelInvoke(func cb);

	void		Invoke(Object* obj, method cb, clocktime t);
	void		CancelInvoke(Object* obj, method cb);

	clocktime	GetDeltaMs();

	void		SetScale(float s);
	float		GetScale() { return m_Scale; }
	
	//----------------------------------------
	// Static interface
	//----------------------------------------
	static void	Update();
	static GameClock* GetClock(ClockID id);
	static void SetClock(GameClock* clock, ClockID id);

private:
	//----------------------------------------
	// Internal types
	//----------------------------------------
	typedef std::vector<Timer*> timerVec;
	typedef timerVec::iterator	timerVecIter;
	typedef std::list<_Invoke*> invokeList;
	typedef invokeList::iterator invokeListIter;
	typedef std::map<ClockID, GameClock*> clockMap;
	typedef clockMap::iterator clockMapIter;
	
	//----------------------------------------
	// Private interface
	//----------------------------------------
	void _update();
	
	//----------------------------------------
	// Members
	//----------------------------------------
	timerVec	m_Timers;
	invokeList   m_Invokes;

	clocktime	m_StartTime;
	clocktime	m_CurTime;
	clocktime	m_Delta;
	float		m_Scale;
	
	//----------------------------------------
	// Static Members
	//----------------------------------------
	static clockMap m_Clocks;
};

// some invoke functions, NOTE: this won't work for class
// methods yet
#define INVOKE(fn, t)					\
    if(GameClock* c = GameClock::GetClock(CLOCK_MAIN))	\
	c->Invoke(fn, t);

#define CANCEL_INVOKE(fn, t)				\
    if(GameClock* c = GameClock::GetClock(CLOCK_MAIN))	\
	c->CancelInvoke(fn);

#define CLASS_INVOKE(fn, t)					\
    if(GameClock* c = GameClock::GetClock(CLOCK_MAIN))		\
	c->Invoke(this, fn, t);

#define CANCEL_CLASS_INVOKE(fn, t)				\
    if(GameClock* c = GameClock::GetClock(CLOCK_MAIN))		\
	c->CancelInvoke(this, fn);

#endif /*__GAME_CLOCK_H__*/
