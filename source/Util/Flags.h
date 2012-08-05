#ifndef __FLAGS_H__
#define __FLAGS_H__

#include <MCore.h>
#include <set>

class Flags
{
 public:
 Flags()
   : m_dirty(true), m_flagString("...") {}
  typedef unsigned int            flag;
  typedef std::set<flag>          flagSet;
  typedef flagSet::iterator       flagSetIter;
  typedef flagSet::const_iterator flagSetConstIter;
  
  flagSet m_flags;
  MString m_flagString;
  
  void Parse();
  bool Contains(flag check) const;
  bool Intersects(Flags check) const;
 private:
  bool m_dirty;
};

#endif/*__FLAGS_H__*/
