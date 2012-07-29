#ifndef __UTIL_H__
#define __UTIL_H__

//--------------------------------------------
// Util namespace
// just somewhere to put some generally useful
// functions
//--------------------------------------------
namespace Util
{
	//----------------------------------------
	// Hash
	// A general purpose hash function
	// http://www.partow.net/programming/hashfunctions/
	//----------------------------------------
	unsigned int Hash(const char* string);
};

#endif /*__UTIL_H__*/