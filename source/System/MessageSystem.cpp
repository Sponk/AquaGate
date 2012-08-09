/* MessageSystem.cpp
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

// Standard includes
#include "MessageSystem.h"

// Project includes
#include "AquaGame.h"
#include "Util/Util.h"

// Engine includes
#include <MEngine.h>

// System includes
#include <algorithm> // std::find

MessageSystem::MessageSystem()
{
}

Message MessageSystem::RegisterMessage(const char* message)
{
    // For now, we will just hash, we could look up to
    // make sure we don't get has clashes...
    return Util::Hash(message);
}

Message RegisterMessage(const char* message)
{
    // This should just wrap up the RegisterMessage function
    // inside the MessageSystem. Making the MessageSystem a
    // singleton would reduce the need for this, but that
    // would not allow us to be able to replace message
    // systems at a later date.
    MEngine* engine = MEngine::getInstance();
    if(MGame* game = engine->getGame())
    {
        AquaGame* tutGame = (AquaGame*)game;

        if(MessageSystem* sys = tutGame->GetMessageSystem())
        {
            return sys->RegisterMessage(message);
        }
    }

    // Do we have a sensible fallback behaviour for if we
    // don't have a message system? Nope. Probably best
    // actually doing a simple incremented ID here to be
    // safe.
    return 0;
}

Observer::~Observer()
{
    std::vector<Subject*>::iterator iSub;
    for(iSub = m_Subjects.begin(); iSub != m_Subjects.end(); ++iSub)
        (*iSub)->DetachObserver(this);

    m_Subjects.clear();
}

void Observer::AttachToSubject(Subject* subject)
{
    std::vector<Subject*>::iterator iSub = std::find(m_Subjects.begin(), m_Subjects.end(), subject);

    if(iSub != m_Subjects.end())
        m_Subjects.erase(iSub);
}

void Subject::AttachObserver(Observer* observer)
{
    // if we're not already being observed by
    // the one being added - then add to the list
    if(std::find(   m_Observers.begin(),
        m_Observers.end(),
        observer) == m_Observers.end())
    {
        m_Observers.push_back(observer);
    }
    observer->AttachToSubject(this);
}
void Subject::DetachObserver(Observer* observer)
{
    // find the correct observer to remove
    observerVecIter iObserver =
        std::find(	m_Observers.begin(),
        m_Observers.end(),
        observer);
    if(iObserver != m_Observers.end())
    {
        m_Observers.erase(iObserver);
    }
}
void Subject::SendMessage(Message message, int param)
{
    // for now, we just send everything to everyone
    // and let them deal with filtering. This isn't
    // an ideal solution, we probably want to extend
    // AttachObserver so we can subscribe to specific
    // messages. 
    observerVecIter iObserver;
    for(iObserver = m_Observers.begin();
        iObserver != m_Observers.end();
        iObserver++)
    {
        (*iObserver)->OnMessage(message, param);
    }
}
