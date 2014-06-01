/** MeshAsset.cpp -- Code file for the MeshAsset class
 *  Peter Turner - Summer 2012 
 */
#include "StdAfx.h"
#include "MeshAsset.h"


MeshAsset::MeshAsset(void) : mesh(0)
{
}


ErrorCode MeshAsset::Init(WCHAR *fileName, Renderer *r, UINT id) {
   ErrorCode err;
   mesh = new Mesh();
//   err = mesh->Init(r);

   if (err != OK) {
      return err;
   }

   err = mesh->LoadObj(fileName);
   if (err != OK) {
      return err;
   }

   this->id = id;
   this->aType = Asset_Mesh;
   return OK;
}


MeshAsset::~MeshAsset(void)
{
   delete mesh;
}
