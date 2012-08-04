#include "BehaviourDB.h"
#include "Util/Util.h"

// BehaviourDB getter. These could have been static functions/members
// but I kept them external as it means one less function call within
// each Behaviour. A little pedantic, I know, but so what.
BehaviourDB g_BehaviourDB;
BehaviourDB* GetBehaviourDB() { return &g_BehaviourDB; }

//--------------------------------------------
// Behaviour
//--------------------------------------------
Behaviour::Behaviour(MObject3d * parentObject, ID id)
: MBehavior(parentObject) 
{
	// On creation, we need to register ourselves
	g_BehaviourDB.RegisterBehaviour(getParentObject(), this, id);
}
//--------------------------------------------
Behaviour::~Behaviour()
{
	// We're not needed any more? Make sure we don't stay in
	// the database
	g_BehaviourDB.RemoveBehaviour(getParentObject(), this);

	std::map<unsigned int, MVariable*>::iterator iVar = m_Variables.begin();

	for(iVar; iVar != m_Variables.end(); ++iVar)
	  delete iVar->second;

	m_Variables.clear();
}
//--------------------------------------------
unsigned int Behaviour::getVariablesNumber()
{
  return m_Variables.size();
}
//--------------------------------------------
MVariable Behaviour::getVariable(unsigned int id)
{
  if(id > m_Variables.size())
    return MVariable("NULL", NULL, M_VARIABLE_NULL);

  std::map<unsigned int, MVariable*>::iterator iVar = m_Variables.begin();

  for(unsigned int i = 0; i < id; ++i)
    ++iVar;

  return *iVar->second;  
}
//--------------------------------------------
Behaviour* Behaviour::GetBehaviour(ID behaviour)
{
	// Just pass the request onto the database
	return g_BehaviourDB.GetBehaviour(getParentObject(), behaviour);
}
//--------------------------------------------
void Behaviour::RegisterVariable(MVariable var)
{
  unsigned int hash = Util::Hash(var.getName());

  m_Variables[hash] = new MVariable(var.getName(), var.getPointer(), var.getType());
}
//--------------------------------------------
void Behaviour::UnregisterVariable(MVariable var)
{
  unsigned int hash = Util::Hash(var.getName());

  std::map<unsigned int, MVariable*>::iterator iVar = m_Variables.find(hash);

  if(iVar != m_Variables.end())
  {
    delete iVar->second;
    m_Variables.erase(iVar);
  }
}
//----------------------------------------
void Behaviour::update()
{
    MEngine* engine = MEngine::getInstance();
    MGame* game = engine->getGame();
    
    if(game == 0 || !game->isRunning())
	return;
    Update();
}
//--------------------------------------------
// BehaviourDB
//--------------------------------------------
Behaviour::ID BehaviourDB::GetBehaviourID(const char* name)
{
	// There are a great many ways we could sort IDs. The
	// simple method used for the messages wouldn't work
	// here as potentially we will call GetBehaviourID
	// multiple times. We could keep a list of already
	// registered behaviours, but that's hassle. Instead
	// we'll just grab a hash of the name. That should
	// be unique enough
	return Util::Hash(name);
}
//--------------------------------------------
Behaviour* BehaviourDB::GetBehaviour(MObject3d* obj, Behaviour::ID id)
{
	// we could just use m_Objects[obj][id] at this point
	// it would even return 0 if there wasn't a behaviour
	// registered. The issue is that it will make empty 
	// entries in our map, which we don't want
	// instead, we'll use map::find to look through the
	// map and pull out what we want
	objectMapIter iObj = m_Objects.find(obj);
	if(iObj != m_Objects.end())
	{
		behaviourMapIter iBehaviour = iObj->second.find(id);
		if(iBehaviour != iObj->second.end())
		{
			return iBehaviour->second;
		}
	}
	return 0;
}
//--------------------------------------------
void BehaviourDB::RemoveBehaviour(MObject3d* obj, Behaviour* behaviour)
{
	// at this point, we can assume that m_Objects[obj] exists
	// so we shouldn't need to do a map::find on that, however
	// we could potentially be looking for a behaviour that
	// has already been removed. So we need to safeguard
	// against that.
	behaviourMapIter iBehaviour = m_Objects[obj].find(behaviour->GetID());
	if(iBehaviour != m_Objects[obj].end())
	{
		m_Objects[obj].erase(iBehaviour);
	}

	// If the object is now empty, we can remove it and save some space
	objectMapIter iObj = m_Objects.find(obj);
	if(iObj->second.size() == 0)
	{
		m_Objects.erase(iObj);
	}
}
//--------------------------------------------
void BehaviourDB::RegisterBehaviour(MObject3d* obj, Behaviour* behaviour, Behaviour::ID id)
{
	// absolutely no point in doing any kind of find behaviour here.
	// just stick it in the map, making new entries where needed
	m_Objects[obj][id] = behaviour;
}
//--------------------------------------------
