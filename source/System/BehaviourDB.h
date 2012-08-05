#ifndef __BEHAVIOUR_DB_H__
#define __BEHAVIOUR_DB_H__

#include <map>

#include <MEngine.h>


//--------------------------------------------
// Behaviour
//
// A little wrapper around MBehaviour to take
// care of a little maintenance. For now just
// inter-behaviour interactions
//--------------------------------------------
class Behaviour : public MBehavior
{
public:
    // typedef the ID so we could potentially
    // change how we refer to behaviours and
    // not have to change all our existing
    // behaviours
    typedef int ID;

    // standard MBehavior constructor, plus our ID
    // for the Behaviour Database
    Behaviour(MObject3d * parentObject, ID id);
    ~Behaviour();

    // This probably won't be used as we need the
    // Behaviour ID to be static
    virtual ID GetID() { return 0; }

    // MBehavior virtuals
    virtual unsigned int getVariablesNumber();
    virtual MVariable getVariable(unsigned int id);
    virtual void update();
protected:
    // This is where the magic happens
    // from within any custom behaviour, we should
    // now be able to call GetBehaviour<SomeBehaviour>()
    // and be given our sibling behaviour (if one of
    // that type exists on the object)
    template <typename T>
    T* GetBehaviour()
    {
        return (T*)GetBehaviour(T::GetStaticID());
    }
    Behaviour* GetBehaviour(ID behaviour);

    void RegisterVariable(MVariable var);
    void UnregisterVariable(MVariable var);

    virtual void Update() = 0;
private:
    std::map<unsigned int, MVariable*> m_Variables;
};

// Some helpwe macros to keep things tidy.
// This one goes within the class definition
#define IMPLEMENT_BEHAVIOUR(x)					\
    static const char* getStaticName() { return #x; }		\
    const char* getName() { return getStaticName(); }		\
    static void SetID(Behaviour::ID id) { m_ID = id; }		\
    static Behaviour::ID GetStaticID() { return m_ID; }		\
    static Behaviour::ID m_ID;					\
    virtual Behaviour::ID GetID() { return x::GetStaticID(); }	\
    void destroy();						\
    static MBehavior* getNew(MObject3d* parentObject);		\
    MBehavior* getCopy(MObject3d* parentObject);		\
    void runEvent(int param){}

// This one goes at the top of the source file
#define REGISTER_BEHAVIOUR(x)						\
    void x::destroy() { delete this; }					\
    MBehavior* x::getNew(MObject3d* parentObject)			\
{ return new x(parentObject); }					\
    MBehavior* x::getCopy(MObject3d* parentObject)			\
{ return new x(*this, parentObject); }				\
    Behaviour::ID x::m_ID = GetBehaviourDB()->GetBehaviourID(#x);	\
class x##AutoRegister						\
{									\
public:								\
    x##AutoRegister()						\
{								\
    MEngine* engine = MEngine::getInstance();			\
    MBehaviorManager* bm = engine->getBehaviorManager();	\
    bm->addBehavior(x::getStaticName(),				\
    M_OBJECT3D,					\
    x::getNew);					\
}								\
};									\
    x##AutoRegister _##x##AutoRegister;

//--------------------------------------------
// BehaviourDB
//
// The behind-the-scenes magic worker.
// It actually does very little. We just need
// to make sure that it's kept up to date with
// the correct behaviours
//--------------------------------------------
class BehaviourDB
{
public:
	// This is possibly the most important function here
	// It gives us a (semi) unique ID for each behaviour
	// without this, we wouldn't know which is which
	Behaviour::ID GetBehaviourID(const char* name);

	// This is the function that we're usually interested in
	// it will look up the correct behaviour and return it,
	// if one exists, otherwise returning null.
	Behaviour* GetBehaviour(MObject3d* obj, Behaviour::ID id);

	template <class T>
	T* GetBehaviour(MObject3d* obj)
	{
	    return (T*)GetBehaviour(obj, T::GetStaticID());
	}

	// In order for the database to know the behaviour exists, 
	// we need to register it, but also, afterwards, we'll need
	// to remove it, otherwise we could potentially be returning
	// old and corrupt information
	void RemoveBehaviour(MObject3d* obj, Behaviour* behaviour);
	void RegisterBehaviour(MObject3d* obj, Behaviour* behaviour, Behaviour::ID id);
private:
    typedef std::map<Behaviour::ID, Behaviour*>	behaviourMap;
    typedef behaviourMap::iterator				behaviourMapIter;
    typedef std::map<MObject3d*, behaviourMap>	objectMap;
    typedef objectMap::iterator					objectMapIter;

    objectMap		m_Objects;
};

// The BehaviourDB is technically a singleton
// so we need a getter
BehaviourDB* GetBehaviourDB();

#endif /*__BEHAVIOUR_DB_H__*/
