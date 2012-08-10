#include "Script.h"

#include "BehaviourFuncs.h"
#include "Broadcaster.h"

#include "Util/Util.h"

int ScriptBroadcastMessage()
{
    MEngine* engine = MEngine::getInstance();
    MScriptContext* script = engine->getScriptContext();

    int num = script->getArgsNumber();
    
    MObject3d* obj   = (MObject3d*)script->getInteger(0);
    const char* msg  =             script->getString (1);
    int param        =  num > 2 ?  script->getInteger(2) : 0;

    Message message = Util::Hash(msg);
    Broadcaster::Broadcast(obj, message, param);

    return 0;
}

void RegisterScriptFunctions()
{
    MEngine* engine = MEngine::getInstance();
    MScriptContext* script = engine->getScriptContext();

    if(script)
    {
	printf("test\n");
	script->addFunction("broadcastMessage", ScriptBroadcastMessage);
	script->addFunction("getBehavior", ScriptGetBehaviour);
	script->addFunction("getParentObject", ScriptGetParentObject);
	script->addFunction("sendMessage", ScriptSendMessage);
	script->addFunction("getVariablesNumber", ScriptGetVariablesNumber);
	script->addFunction("getVariableName", ScriptGetVariableName);
	script->addFunction("getVariable", ScriptGetVariable);
	script->addFunction("setVariable", ScriptSetVariable);
    }
}
