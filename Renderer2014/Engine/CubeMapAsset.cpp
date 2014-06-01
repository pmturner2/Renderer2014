/** CubeMapAsset.cpp -- Code file for the CubeMapAsset class
 *  Peter Turner - Summer 2012 
 */
#include "StdAfx.h"
#include "CubeMapAsset.h"


CubeMapAsset::CubeMapAsset(void)// : cubeMap(0)
{
}


CubeMapAsset::~CubeMapAsset(void)
{
 //  if (cubeMap) {
 ////     cubeMap->Release();
 //  }
}

ErrorCode CubeMapAsset::Init(WCHAR *fileName, Renderer *r, UINT id) {      
	/*
   this->id = id;
   this->aType = Asset_CubeMap;

   return r->CreateCubeMap(fileName, &cubeMap);
   */
	return OK;
}
