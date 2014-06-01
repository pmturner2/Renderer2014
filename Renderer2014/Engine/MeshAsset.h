/** MeshAsset.h -- Header file for the MeshAsset class
 *  Peter Turner - Summer 2012 
 */
#pragma once
#include "asset.h"
#include "Mesh.h"
#include "Renderer.h"
#include "ErrorManager.h"

class MeshAsset :  public Asset
{
public:
   MeshAsset(void);
   ~MeshAsset(void);
   
   // Initializes the Texture. ID should be predefined from Asset Manager's
   //    hash function.
   ErrorCode Init(WCHAR *fileName, Renderer *r, UINT id);

   Mesh *GetMesh() { return mesh; }
   
   // TODO: UNLOAD FUNCTION
private:
   Mesh *mesh;
};

