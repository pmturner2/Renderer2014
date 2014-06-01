/** Asset.cpp -- Code File for the Asset class
 *  Peter Turner - Summer 2012 
 */

#include "StdAfx.h"
#include "Asset.h"


Asset::Asset(void)
{
}


Asset::~Asset(void)
{
}


bool Asset::operator ==(const Asset &rhs) const {
   return (this->id == rhs.id);
}


bool Asset::operator ==(const UINT &rhs) const {
   return (this->id == rhs);
}


bool Asset::operator <(const Asset &rhs) const {
   return (this->id < rhs.id);
}


bool Asset::operator <(const UINT &rhs) const {
   return (this->id < rhs);
}


bool Asset::operator >(const Asset &rhs) const {
   return (this->id > rhs.id);
}


bool Asset::operator >(const UINT &rhs) const {
   return (this->id > rhs);
}
