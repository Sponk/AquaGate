/* ObjectFlags.h
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


#ifndef __OBJECT_FLAGS_H__
#define __OBJECT_FLAGS_H__

#include "System/BehaviourDB.h"

#include <set>

//----------------------------------------
// ObjectFlags
//----------------------------------------
class ObjectFlags : public Behaviour
{
public:
	ObjectFlags(MObject3d * parentObject);
	ObjectFlags(ObjectFlags & behavior, MObject3d * parentObject);
	~ObjectFlags();
	
	//--------------------------------
	// Behaviour virtuals
	//--------------------------------
	void Update(){}

	IMPLEMENT_BEHAVIOUR(ObjectFlags);

	class Flags
	{
	public:
	    Flags()
		: m_dirty(true) {}
	    typedef unsigned int            flag;
	    typedef std::set<flag>          flagSet;
	    typedef flagSet::iterator       flagSetIter;
	    typedef flagSet::const_iterator flagSetConstIter;
	    
	    flagSet m_flags;
	    MString m_flagString;

	    void Parse();
	    bool Contains(flag check) const;
	    bool Intersects(Flags check) const;
	private:
	    bool m_dirty;
	};

	const Flags::flagSet& GetFlags();
private:
	void Init();

	Flags m_flags;
};

#endif /*__OBJECT_FLAGS_H__*/
