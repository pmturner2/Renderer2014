/** AssetManager.h -- Header file for the AssetManager class
 *  Peter Turner - Summer 2012 
 */
#pragma once

#include "Renderer.h"
#include "BST.h"
#include "Asset.h"
#include "Mesh.h"
#include "MeshAsset.h"
#include "TextureAsset.h"
#include "CubeMapAsset.h"
#include "ErrorManager.h"
#include "MathDefs.h"

/** class AssetManager
 *    Manages all game assets: Textures, Meshes, etc. 
 *    Responsible for allocating and deleting all memory associated with them
 *    Uses a hashing function to turn file names into 32-bit IDs, then stores
 *    everything in a BST. 
 */
class AssetManager
{
public:
   AssetManager();
   ~AssetManager(void);

   // Sets the renderer and allocates the BST
   ErrorCode Init(Renderer *r);
   
   // Returns the hashed 32-bit ID from the string
   UINT GetAssetId(WCHAR *string);

   // Returns the Asset with the specified string, or creates and adds to BST
   MeshAsset *CreateMesh(WCHAR *string);

   // Not yet implemented
   Mesh *GetMesh(WCHAR *string);

   // Returns the Asset's Contents with the specified ID
   Mesh *GetMesh(UINT id);
      
   // Returns the Asset with the specified string, or creates and adds to BST
   TextureAsset *CreateTexture(const char * string);   

   // Not yet implemented
   TextureAsset *GetTexture(WCHAR *string);

   // Returns the Asset's Contents with the specified ID
   TextureAsset *GetTexture(UINT id); 

   /*
   // Returns the Asset with the specified string, or creates and adds to BST
   CubeMapAsset *CreateCubeMap(WCHAR *string);   

   // Not yet implemented
   CubeMap *GetCubeMap(WCHAR *string);

   // Returns the Asset's Contents with the specified ID
   CubeMap *GetCubeMap(UINT id);
   */
private:
   Renderer *r;
   BST<Asset> *assets;

   /*
    * These are level specific assets, which are wiped on level load.
    * Level specific npc, etc
    */
   BST<Asset> *levelAssets;      
};

