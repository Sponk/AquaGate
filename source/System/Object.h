#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Util/Util.h"

#ifdef DEBUG
# include <string>
#endif

class Object
{
public:
    Object(const char* name);

    unsigned int m_Hash;

#ifdef DEBUG
    std::string m_Name;
#endif
};

#endif/*__OBJECT_H__*/
