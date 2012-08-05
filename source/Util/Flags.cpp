#include "Flags.h"
#include "Util.h"

//----------------------------------------
// Flags
//----------------------------------------
void Flags::Parse()
{
    if(m_dirty)
    {
	m_dirty = false;

	tokenizer_t tok = tokenizer(m_flagString.getData(), ",", TOKENIZER_EMPTIES_OK);
	const char* token;
	for(token = tokenize(&tok); token; token = tokenize(&tok))
	    m_flags.insert(Util::Hash(token));
	free_tokenizer(&tok);
    }
}
//----------------------------------------
bool Flags::Contains(flag check) const
{
    return m_flags.find(check) != m_flags.end();
}
//----------------------------------------
bool Flags::Intersects(Flags check) const
{
    for(flagSetConstIter iFlag = m_flags.begin(); iFlag != m_flags.end(); iFlag++)
	if(Contains(*iFlag))
	    return true;
    return false;
}
