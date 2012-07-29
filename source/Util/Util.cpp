
#include "Util.h"
#include <cstring>

// BPHash function as found on
// http://www.partow.net/programming/hashfunctions/
unsigned int Util::Hash(const char* str)
{
	unsigned int len = strlen(str);
	unsigned int hash = 0;
	unsigned int i    = 0;
	for(i = 0; i < len; str++, i++)
	{
		hash = hash << 7 ^ (*str);
	}

	return hash;
}

int Util::Pow2(int x)
{
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}
