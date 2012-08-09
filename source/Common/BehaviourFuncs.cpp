#include "BehaviourFuncs.h"

#include "System/BehaviourDB.h"
#include "MEngine.h"

MScriptContext* GetScript()
{
    MEngine* engine = MEngine::getInstance();
    return engine->getScriptContext();
}

bool HasArgs(int num)
{
    return GetScript()->getArgsNumber() == num;
}

int ScriptGetBehaviour()
{
    MScriptContext* script = GetScript();
    if(HasArgs(2))
    {
	MObject3d* obj = (MObject3d*)script->getInteger(0);
	const char* name = script->getString(1);
	Behaviour::ID id = GetBehaviourDB()->GetBehaviourID(name);

	script->pushInteger((int)GetBehaviourDB()->GetBehaviour(obj, id));
    }
    else
	script->pushInteger(-1);

    return 1;
}

int ScriptGetParentObject()
{
    MScriptContext* script = GetScript();
    if(HasArgs(1))
    {
	MBehavior* behavior = (MBehavior*)script->getInteger(0);

	script->pushInteger((int)behavior->getParentObject());
    }
    else
	script->pushInteger(-1);

    return 1;   
}
int ScriptSendMessage()
{
    MScriptContext* script = GetScript();
    if(HasArgs(3) || HasArgs(2))
    {
	Behaviour* behaviour = (Behaviour*)script->getInteger(0);
	const char* msg      = script->getString (1);
	unsigned int param = 0;
	if(HasArgs(3))
	    param            = (unsigned int)script->getInteger(2);
    }
}

int ScriptGetVariablesNumber()
{
    MScriptContext* script = GetScript();
    if(HasArgs(1))
    {
	MBehavior* behavior = (MBehavior*)script->getInteger(0);

	script->pushInteger(behavior->getVariablesNumber());
    }
    else
	script->pushInteger(-1);
    
    return 1;
}

int ScriptGetVariableName()
{
    MScriptContext* script = GetScript();
    if(HasArgs(2))
    {
	MBehavior* behavior = (MBehavior*)script->getInteger(0);
	int var = script->getInteger(1);

	script->pushString(behavior->getVariable(var).getName());
    }
    else
	script->pushString("");
    return 1;
}

int ScriptGetVariable()
{
    MScriptContext* script = GetScript();
    if(HasArgs(2))
    {
	MBehavior* behavior = (MBehavior*)script->getInteger(0);
	int varid = script->getInteger(1);
	MVariable var = behavior->getVariable(varid);

	switch(var.getType())
	{
	case M_VARIABLE_NULL:
	{
	    break;
	}
	case M_VARIABLE_BOOL:
	{
	    script->pushBoolean(*(bool*)var.getPointer());
	    break;
	}
	case M_VARIABLE_INT:
	{
	    script->pushInteger(*(int*)var.getPointer());
	    break;
	}
	case M_VARIABLE_UINT:
	{
	    script->pushInteger(*(unsigned int*)var.getPointer());
	    break;
	}
	case M_VARIABLE_FLOAT:
	{
	    script->pushFloat(*(float*)var.getPointer());
	    break;
	}
	case M_VARIABLE_STRING:
	{
	    MString* str = (MString*)var.getPointer();
	    script->pushString(str->getData());
	    break;
	}
	case M_VARIABLE_VEC2:
	{
	    float* vec = (float*)var.getPointer();
	    script->pushFloatArray(vec, 2);
	    break;
	}
	case M_VARIABLE_VEC3:
	{
	    float* vec = (float*)var.getPointer();
	    script->pushFloatArray(vec, 3);
	    break;
	}
	case M_VARIABLE_VEC4:
	{
	    float* vec = (float*)var.getPointer();
	    script->pushFloatArray(vec, 4);
	    break;
	}
	case M_VARIABLE_QUAT:
	{
	    MQuaternion* quat = (MQuaternion*)var.getPointer();
	    script->pushFloatArray(quat->values, 2);
	    break;
	}
	case M_VARIABLE_TEXTURE_REF:
	{
	    break;
	}
	default:
	{
	    script->pushInteger(-1);
	}
	}
    }
    else
	script->pushInteger(-1);
    
    return 1;
}

int ScriptSetVariable()
{
    MScriptContext* script = GetScript();
    if(HasArgs(3))
    {
	MBehavior* behavior = (MBehavior*)script->getInteger(0);
	int varid = script->getInteger(1);
	MVariable var = behavior->getVariable(varid);

	switch(var.getType())
	{
	case M_VARIABLE_NULL:
	{
	    break;
	}
	case M_VARIABLE_BOOL:
	{
	    *((bool*)var.getPointer()) = (bool)script->getInteger(2);
	    break;
	}
	case M_VARIABLE_INT:
	case M_VARIABLE_UINT:
	{
	    *((int*)var.getPointer()) = script->getInteger(2);
	    break;
	}
	case M_VARIABLE_FLOAT:
	{
	    *((float*)var.getPointer()) = script->getFloat(2);
	    break;
	}
	case M_VARIABLE_STRING:
	{
	    MString str(script->getString(2));
	    *((MString*)var.getPointer()) = str;
	    break;
	}
	case M_VARIABLE_VEC2:
	{
	    break;
	}
	case M_VARIABLE_VEC3:
	{
	    break;
	}
	case M_VARIABLE_VEC4:
	{
	    break;
	}
	case M_VARIABLE_QUAT:
	{
	    break;
	}
	case M_VARIABLE_TEXTURE_REF:
	{
	    break;
	}
	default:
	{
	    script->pushInteger(-1);
	}
	}
    }
    else
	script->pushInteger(-1);
    
    return 0;
}
