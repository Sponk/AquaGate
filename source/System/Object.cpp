#include "Object.h"

#include "Util/Util.h"

Object::Object(const char* name)
{
#ifdef DEBUG
    m_Name = name;
#endif
    
    m_Hash = Util::Hash(name);
}
