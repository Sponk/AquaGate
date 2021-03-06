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

	// returns smallest power of 2 which is greater than the value supplied
	int Pow2(int x);
};


#include "c_tokenizer.h"

//--------------------------------------------
// typedef's
//--------------------------------------------
typedef long int clocktime;
typedef unsigned int ClockID;

#include <MCore.h>
#include <MFileTools.h>
#include <stdio.h>

#ifndef MFile
# define MFile FILE
#endif

#ifndef  M_fopen
# define M_fopen fopen
#endif

#ifndef  M_fclose
# define M_fclose fclose
#endif

#ifndef  M_fread
# define M_fread fread
#endif

#ifndef  M_fwrite
# define M_fwrite fwrite
#endif

#ifndef  M_fprintf
# define M_fprintf fprintf
#endif

#ifndef  M_fseek
# define M_fseek fseek
#endif

#ifndef  M_ftell
# define M_ftell ftell
#endif

#ifndef  M_rewind
# define M_rewind rewind
#endif

#ifdef WIN32
# ifndef max
#  define max(x, y) (x > y ? x : 0)
# endif

# ifndef min
#  define min(x, y) (x < y ? x : 0)
# endif

# ifndef clamp
#  define clamp(x, low, hi) (max(min(x, hi), low))
# endif
#endif

#define STRINGISE_IMPL(x) #x
#define STRINGISE(x) STRINGISE_IMPL(x)

// http://stackoverflow.com/questions/471935/user-warnings-on-msvc-and-gcc
// Use: #pragma message WARN("My message")
#if _MSC_VER
#   define FILE_LINE_LINK __FILE__ "(" STRINGISE(__LINE__) ") : "
#   define WARN(exp) (FILE_LINE_LINK "WARNING: " exp)
#else//__GNUC__ - may need other defines for different compilers
#   define WARN(exp) ("WARNING: " exp)
#endif


#endif /*__UTIL_H__*/
