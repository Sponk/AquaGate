#ifndef __BROADCASTER_H__
#define __BROADCASTER_H__

#include "System/BehaviourDB.h"

//----------------------------------------
// Broadcaster
// 
// Acts as a relay for messages between
// entities
//----------------------------------------
class Broadcaster : public Subject, public Behaviour
{
public:
    Broadcaster(MObject3d * parentObject);
    Broadcaster(Broadcaster & behavior, MObject3d * parentObject);
    ~Broadcaster();

    //--------------------------------
    // Behaviour virtuals
    //--------------------------------
    void Update(){}
    IMPLEMENT_BEHAVIOUR(Broadcaster);

    //--------------------------------
    // Observer virtuals
    //--------------------------------
    void OnMessage(Message message, int param);

    //--------------------------------
    // Static helper API
    //--------------------------------
    static void Broadcast(MObject3d* obj, Message message, int param = 0);
    static void Broadcast(int objID, Message message, int param = 0);
};

#endif/*__BROADCASTER_H__*/
