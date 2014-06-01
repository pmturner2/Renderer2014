/** Asset.h -- Header file for the Asset class
 *  Peter Turner - Summer 2012 
 */
#pragma once

enum assetType { Asset_Mesh, Asset_Texture, Asset_CubeMap};

/** class Asset - abstract class representing a type of asset.
 *    subclasses are a particular type of asset (mesh, texture, etc).
 */
class Asset
{
public:
   Asset(void);
   virtual ~Asset(void);

   // Comparison operators.  Compares id.
   bool operator ==(const Asset &rhs) const;
   bool operator ==(const UINT &rhs) const;
   bool operator <(const Asset &rhs) const;
   bool operator <(const UINT &rhs) const;
   bool operator >(const Asset &rhs) const;
   bool operator >(const UINT &rhs) const;

   UINT id; // hashed id from file name
    
   assetType aType;
};

