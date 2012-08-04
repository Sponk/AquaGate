/* ObjectFlags.cpp
  version 0.0.2, August 2st, 2012

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
   0.0.2 - 01.08.2012 - Renamed to ObjectFlags. Added state machine
                        skeleton to handle controlling the player. - PG
   0.0.1 - 12.02.2012 - Implemented as TuturialBehaviour for 
                        http://nistur.com - PG
*/

#include "ObjectFlags.h"
#include "Util.h"

#include <MEngine.h>

REGISTER_BEHAVIOUR(ObjectFlags);

//----------------------------------------
// quick defines
//----------------------------------------

//----------------------------------------
// ObjectFlags
//----------------------------------------
ObjectFlags::ObjectFlags(MObject3d * parentObject)
    : Behaviour(parentObject, GetStaticID())
{
    Init();
}
//----------------------------------------
ObjectFlags::ObjectFlags(ObjectFlags & behavior, 
				   MObject3d * parentObject)
    : Behaviour(parentObject, GetStaticID())
{
    Init();
}
//----------------------------------------
ObjectFlags::~ObjectFlags(void)
{
}
//----------------------------------------
void ObjectFlags::Init()
{
    RegisterVariable(MVariable("Flags", &m_flags.m_flagString, M_VARIABLE_STRING));
}
//----------------------------------------
const ObjectFlags::Flags::flagSet& ObjectFlags::GetFlags()
{
    m_flags.Parse();
    return m_flags.m_flags;
}
//----------------------------------------
// Flags
//----------------------------------------
void ObjectFlags::Flags::Parse()
{
    if(m_dirty)
    {
	m_dirty = false;

	tokenizer_t tok = tokenizer(m_flagString.getData(), ",", TOKENIZER_EMPTIES_OK);
	const char* token;
	for(token = tokenize(&tok); token; token = tokenize(&tok))
	    m_flags.insert(Util::Hash(token));
	free_tokenizer(&tok);
    }
}
//----------------------------------------
bool ObjectFlags::Flags::Contains(flag check) const
{
    return m_flags.find(check) != m_flags.end();
}
//----------------------------------------
bool ObjectFlags::Flags::Intersects(ObjectFlags::Flags check) const
{
    for(flagSetConstIter iFlag = m_flags.begin(); iFlag != m_flags.end(); iFlag++)
	if(Contains(*iFlag))
	    return true;
    return false;
}
