/** Mesh.h -- Header file for Mesh Class
 *  Peter Turner - Summer 2012
 */
#pragma once
#include "GeometryDefs.h"
#include "stdafx.h"
#include "ErrorManager.h"

/** class Mesh - Geometry Mesh
 */
class Mesh
{
public:
   Mesh(void);   
   ~Mesh(void);

   // Loads mesh data from .OBJ file
   ErrorCode LoadObj(WCHAR *fileName);

   // Draws the mesh
   ErrorCode Draw();   

#ifdef DX11
   
   // sets Renderer
   ErrorCode Init(Renderer *r);

   void SetVbuffer(VBuffer *v) { vBuffer = v; }
   void SetIbuffer(IBuffer *i) { iBuffer = i; }
#endif
   void SetICount(UINT i) { iCount = i; }
   void GetLocalExtents(vec3 &outMin, vec3&outMax);

   // Todo: Incorporate Animations.
   void ComputeLocalExtents();
private:
   // Total index count
   UINT iCount;

   UINT vBufferSize;

   // Size of our vertex in bytes
   UINT stride;


   Vertex_PTT *vertBuff; // Stores vertices from which we make our VBuffer
   vec3 m_localMinimumExtent;
   vec3 m_localMaximumExtent;
#ifdef GL
	unsigned int vaoId[1];
	unsigned int vboId[1]; 
	unsigned int iboId[1];
#else
    // Array of Struct (pos, tc, normal, tang)
   VBuffer *vBuffer;
   
   Renderer *r;
   // Array of Shorts
   IBuffer *iBuffer;
#endif

   
};


