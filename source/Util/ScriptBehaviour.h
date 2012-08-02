/* ScriptBehaviour.h
  version 0.0.2, August 2nd, 2012

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

/* Changelog
   0.0.2 - 01.08.2012 - Renamed to ScriptBehaviour. Added state machine
                        skeleton to handle controlling the player. - PG
   0.0.1 - 12.02.2012 - Implemented as TuturialBehaviour for 
                        http://nistur.com - PG
*/


#ifndef __PLAYER_CONTROLLER_H__
#define __PLAYER_CONTROLLER_H__

#include "System/Timer.h"

#include "System/MessageSystem.h"

#include "System/BehaviourDB.h"

//--------------------------------------------
// ScriptBehaviour
//--------------------------------------------
class ScriptBehaviour : public Behaviour, public Observer
{
public:
	ScriptBehaviour(MObject3d * parentObject);
	ScriptBehaviour(ScriptBehaviour & behavior, MObject3d * parentObject);
	~ScriptBehaviour();
	
	//----------------------------------------
	// MBehavior virtuals
	//----------------------------------------
	void destroy();
	static MBehavior* getNew(MObject3d* parentObject);
	MBehavior* getCopy(MObject3d* parentObject);

	void update();
	void runEvent(int param){}

	//----------------------------------------
	// Observer virtuals
	//----------------------------------------
	void OnMessage(Message message, int param1);

	IMPLEMENT_BEHAVIOUR(ScriptBehaviour);
private:
	void Init();

	MString m_FunctionName;
};

#endif /*__PLAYER_CONTROLLER_H__*/
