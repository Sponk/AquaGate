#ifndef __INVOKE_H__
#define __INVOKE_H__

#include "System/Object.h"

#ifdef CAN_INVOKE
# ifdef IN_GAME_CLOCK_H

typedef void(*func)(void);

//--------------------------------------------
// Invoke types
// 
// used internally. Can be safely ignored
//--------------------------------------------
class _Invoke
{
public:
    _Invoke(clocktime t)
    : _time(t) {}
    void Tick(clocktime dt)
    {
	_time -= dt;
	if(_time <= 0)
	    Invoke();
    }
    virtual void Invoke() = 0;
    virtual bool Zombie() const { return _time <= 0; }
    virtual bool Is(const char* type) = 0;
private:
    clocktime _time;
};

class Function : public _Invoke
{
public:
    Function(func f, clocktime t)
    : _function(f)
    , _Invoke(t)
    {}

    virtual void Invoke() { if(_function) _function(); }
    virtual bool Zombie() const { return !_function || _Invoke::Zombie(); }
    virtual bool Is(const char* type) { return strcmp(type, "Function") == 0; }

    bool Compare(func f) { return f == _function; }
private:
    func _function;
};

template <typename ObjectType>
class Method : public _Invoke
{
public:
	Method(ObjectType* o, void (ObjectType::*m)(void), clocktime t)
	: _object(o), _method(m), _Invoke(t) {}
	void Invoke()
	{
		(*_object.*_method)();
	}
	void (ObjectType::*_method)(void);
	ObjectType* _object;

    virtual bool Zombie() const { return !_method || !_object || _Invoke::Zombie(); }
    virtual bool Is(const char* type) { return strcmp(type, "Method") == 0; }
   
    bool Compare(ObjectType* o, void (ObjectType::*m)(void)) { return o == _object && m == _method; }
};
# else
#  pragma message WARN("Looks like you're trying to include Invoke.h manually. This won't work")
# endif
#endif

#endif/*__INVOKE_H__*/
