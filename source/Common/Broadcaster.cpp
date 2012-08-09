#include "Broadcaster.h"
#include "Util/Util.h"

REGISTER_BEHAVIOUR(Broadcaster);
Broadcaster::Broadcaster(MObject3d * parentObject)
    : Behaviour(parentObject, GetStaticID())
{
}

Broadcaster::Broadcaster(Broadcaster & behavior, MObject3d * parentObject)
    : Behaviour(parentObject, GetStaticID())
{
}

Broadcaster::~Broadcaster()
{
}

void Broadcaster::OnMessage(Message message, int param)
{
    SendMessage(message, param);

// also send to script
    MEngine* engine = MEngine::getInstance();
    MScriptContext* script = engine->getScriptContext();

    script->pushInteger((int)getParentObject());
    script->pushInteger(message);
    script->pushInteger(param);
    script->callFunction("onMessage", 3);
}

void Broadcaster::Broadcast(MObject3d* obj, Message message, int param)
{
    if(Broadcaster* bc = GetBehaviourDB()->GetBehaviour<Broadcaster>(obj))
        bc->OnMessage(message, param);
}

void Broadcaster::Broadcast(int objID, Message message, int param)
{
    MEngine* engine = MEngine::getInstance();
    MLevel*  level  = engine ? engine->getLevel() : 0;
    MScene*  scene  = level ? level->getCurrentScene() : 0;
    if(scene)
        Broadcast(scene->getObjectByIndex(objID), message, param);
}
