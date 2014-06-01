/** AssetManager.cpp -- Code file for the AssetManager class
 *  Peter Turner - Summer 2012 
 */
#include "StdAfx.h"
#include "AssetManager.h"

//----------------------------------------------------------------------------

AssetManager::AssetManager() :  assets(0), levelAssets(0)
{}

//----------------------------------------------------------------------------

AssetManager::~AssetManager(void)
{   
   if (assets) {
      delete assets;
   }
}

//----------------------------------------------------------------------------

ErrorCode AssetManager::Init(Renderer *r) {
   this->r = r;
   assets = new BST<Asset>();

   if (assets == NULL) {
      return Error_AllocatingResource;
   }
   return OK;
}

//----------------------------------------------------------------------------

UINT AssetManager::GetAssetId(WCHAR *string) {
   UINT target = Hash(string);
   return target;
}

//----------------------------------------------------------------------------

MeshAsset *AssetManager::CreateMesh(WCHAR *string) {
   UINT targetId = Hash(string);
   Asset *targetAsset = assets->Find(targetId);

   if (targetAsset != NULL) { // Already Exists, so return it.
      if (targetAsset->aType == Asset_Mesh) {
         return (MeshAsset *)targetAsset;
      } else {
         return NULL;
      }      
   } else { // Create new Mesh      
      MeshAsset *ma = new MeshAsset();
      ma->Init(string, r, targetId);

      assets->Insert((Asset *) ma);
      return ma;
   }
}

//----------------------------------------------------------------------------

Mesh* AssetManager::GetMesh(UINT mId) {
   MeshAsset *mAsset = ((MeshAsset*) assets->Find(mId));

   if (mAsset != NULL) {
      if (mAsset->aType == Asset_Mesh) {
         return mAsset->GetMesh();   
      }
   } 
   return NULL;   
}

//----------------------------------------------------------------------------

TextureAsset *AssetManager::CreateTexture(const char *string) {
   UINT targetId = Hash((WCHAR *)string);
   Asset *targetAsset = assets->Find(targetId);

   if (targetAsset != NULL) { // Already Exists, so return it.
      if (targetAsset->aType == Asset_Texture) {
         return (TextureAsset *)targetAsset;
      } else {
         return NULL;
      }
   } else { // Create new Texture      
      TextureAsset *ta = new TextureAsset();
      ta->Init(string, targetId);

      assets->Insert((Asset *) ta);
      return ta;
   }   
}

//----------------------------------------------------------------------------


TextureAsset *AssetManager::GetTexture(UINT tId) {
   TextureAsset *tAsset = ((TextureAsset *) assets->Find(tId));
   
   if (tAsset != NULL) {
      if (tAsset->aType == Asset_Texture) {
         return tAsset;
      }
   } 
   return NULL;   
}

//----------------------------------------------------------------------------
/*

CubeMapAsset *AssetManager::CreateCubeMap(WCHAR *string) {
   UINT targetId = Hash(string);
   Asset *targetAsset = assets->Find(targetId);

   if (targetAsset != NULL) { // Already Exists, so return it. As long as it's the proper type.
      if (targetAsset->aType == Asset_CubeMap) { 
         return (CubeMapAsset *)targetAsset;
      } else {
         return NULL;
      }
   } else { // Create new CubeMap      
      CubeMapAsset *ta = new CubeMapAsset();
      ta->Init(string, r, targetId);

      assets->Insert((Asset *) ta);
      return ta;
   }
}

//----------------------------------------------------------------------------


CubeMap* AssetManager::GetCubeMap(UINT tId) {
   CubeMapAsset *tAsset = ((CubeMapAsset*) assets->Find(tId));

   if (tAsset != NULL) {
      if (tAsset->aType == Asset_CubeMap) {
         return tAsset->GetCubeMap();
      }
   } 
   return NULL;   
}
*/