/** TextureAsset.h -- Header file for the TextureAsset class
 *  Peter Turner - Summer 2012 
 */

#pragma once
#include "stdafx.h"
#include "asset.h"
#include "ErrorManager.h"
#include "imported/stb_image.h"

class TextureAsset : public Asset
{
public:
   TextureAsset(void);
   ~TextureAsset(void);

   // Initializes the Texture. ID should be predefined from Asset Manager's
   //    hash function.
   ErrorCode Init(const char *fileName, UINT id);
   void Bind();

 //  Texture *GetTexture() { return textureView; }

private:
  // Texture *textureView;
	int x;
	int y;
	int n;
	
	unsigned int tex;
};

