/* MessageSystem.h
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

#ifndef __MESSAGE_SYSTEM_H__
#define __MESSAGE_SYSTEM_H__

typedef unsigned int Message;

//----------------------------------------
// Message System
//
// Currently just a simple wrapper for an
// ID. Can be extended to a more complete
// message system
//----------------------------------------
class MessageSystem
{
public:
	MessageSystem();
	Message RegisterMessage(const char* message);
private:
	Message m_CurrID;
};

// RegisterMessage
// quick accessor for the message system
Message RegisterMessage(const char* message);


// DECLARE_MESSAGE
// this macro should be used in header files to
// expose messages you wish to be sent externally
#define DECLARE_MESSAGE(msg) \
	extern Message msg;

// REGISTER_MESSAGE
// this macro should go into the source file
#define REGISTER_MESSAGE(msg) \
	Message msg = RegisterMessage(#msg);

#include <vector>

class Subject;
//----------------------------------------
// Observer
// 
// Currently just an interface for subject
// to send messages to
// Could be extended to automatically
// remove itself from subjects on destruction
//----------------------------------------
class Observer
{
public:
    ~Observer();

    virtual void OnMessage(Message message, int param) = 0;
    
    void AttachToSubject(Subject* subject);

private:
    std::vector<Subject*> m_Subjects;
};

//----------------------------------------
// Subject
// 
// Base class for anything wanting to send
// messages
//----------------------------------------
class Subject
{
public:
	void AttachObserver(Observer* observer);
	void DetachObserver(Observer* observer);

protected:
	void SendMessage(Message message, int param = 0);

private:
	typedef std::vector<Observer*>	observerVec;
	typedef observerVec::iterator	observerVecIter;

	observerVec		m_Observers;
};

#endif /*__MESSAGE_SYSTEM_H__*/
