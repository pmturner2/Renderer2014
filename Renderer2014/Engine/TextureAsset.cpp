/** TextureAsset.cpp -- Code file for the TextureAsset class
 *  Peter Turner - Summer 2012 
 */

//#include "StdAfx.h"
#include "TextureAsset.h"


TextureAsset::TextureAsset(void) //: textureView(0)
{
	tex = 0;
}


TextureAsset::~TextureAsset(void)
{
  // if (textureView) {
  //    textureView->Release();
   //}   
}

void TextureAsset::Bind()
{
	glBindTexture (GL_TEXTURE_2D, tex);
}

ErrorCode TextureAsset::Init(const char *fileName, UINT id) {
   this->id = id;
   this->aType = Asset_Texture;

#ifdef GL
   int force_channels = 4;
  
   unsigned char* image_data = stbi_load ((const char *)fileName, &x, &y, &n, force_channels);
	if (!image_data) {
	  fprintf (stderr, "ERROR: could not load %s\n", fileName);
	}

	tex = 0;

	glGenTextures (1, &tex);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, tex);
	glTexImage2D (
	  GL_TEXTURE_2D,
	  0,
	  GL_RGBA,
	  x,
	  y,
	  0,
	  GL_RGBA,
	  GL_UNSIGNED_BYTE,
	  image_data
	);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	return OK;
#else
   return r->CreateTexture(fileName, &textureView);   
#endif
}

