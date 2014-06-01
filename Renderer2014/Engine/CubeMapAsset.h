/** CubeMapAsset.h -- Header file for the CubeMapAsset class
 *  Peter Turner - Summer 2012 
 */

#pragma once

#include "asset.h"
#include "Renderer.h"
#include "ErrorManager.h"

class CubeMapAsset :  public Asset
{
public:
   CubeMapAsset(void);
   ~CubeMapAsset(void);
   
   // Initializes the CubeMap. ID should be predefined from Asset Manager's
   //    hash function.
   ErrorCode Init(WCHAR *fileName, Renderer *r, UINT id);

  // CubeMap *GetCubeMap() { return cubeMap; }

private:
  // CubeMap *cubeMap;
};

