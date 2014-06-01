#include "MathDefs.h"
#include "stdafx.h"


UINT Hash(WCHAR *string) {
   __int64 hCode = 1;
   UINT prime = 104729;
   UINT returnCode = 0, twoTo32 = 4294967295;
   UINT scale = 0;
   __int32 i = 0;

   while (string[i] != 0) {
      if (i == 0 || i == 3 || i == 7 || i == 13 || i == 29 || i == 53 || i == 97) {
         scale += (UINT) (string[i]);
      }      
      i++;
   }
   scale *= prime;

   i = 0;
   while (string[i] != 0) {
      hCode += (__int64) (scale * string[i]);
      i++;
   }
   returnCode = hCode % twoTo32;
   return returnCode;
}


UINT Hash(char *string) {
   __int64 hCode = 1;
   UINT prime = 104729;
   UINT returnCode = 0, twoTo32 = 4294967295;
   UINT scale = 0;
   __int32 i = 0;

   while (string[i] != 0) {
      if (i == 0 || i == 3 || i == 7 || i == 13 || i == 29 || i == 53 || i == 97) {
         scale += (UINT) (string[i]);
      }      
      i++;
   }
   scale *= prime;

   i = 0;
   while (string[i] != 0) {
      hCode += (__int64) (scale * string[i]);
      i++;
   }
   returnCode = hCode % twoTo32;
   return returnCode;
}

#ifdef DX_11

/** MathDefs.cpp - Code file for Vector/Matrix Math functions.  
 *  Peter Turner - Spring 2012
 *  Wrapped D3DX functions, to ease a transition to OpenGL or another Graphics API.
 */

/*
void Normalize(Vec2 *vIn, Vec2 *vOut) { D3DXVec2Normalize(vOut, vIn); }
void Normalize(Vec3 *vIn, Vec3 *vOut) { D3DXVec3Normalize(vOut, vIn); }
void Normalize(Vec4 *vIn, Vec4 *vOut) { D3DXVec4Normalize(vOut, vIn); }

void Cross(Vec3 *pOut, Vec3 *pV1, Vec3 *pV2) {   D3DXVec3Cross(pOut, pV1, pV2); }
float Dot(Vec3 *pV1, Vec3 *pV2) {   return D3DXVec3Dot( pV1, pV2); }

float Length(const Vec2 *v) { return D3DXVec2Length(v); }
float Length(const Vec3 *v) { return D3DXVec3Length(v); }
float Length(const Vec4 *v) { return D3DXVec4Length(v); }

void Mat4LookAtLH(Mat4 *pOut, const Vec3 *pEye, const Vec3 *pAt, const Vec3 *pUp) { 
   D3DXMatrixLookAtLH(pOut, pEye, pAt, pUp); 
}

void Mat4Identity(Mat4 *pOut) { D3DXMatrixIdentity(pOut); }

void Mat4OrthoLH(Mat4 *pOut, float w, float h, float zn, float zf) { 
   D3DXMatrixOrthoLH(pOut, w, h, zn, zf); 
} 

void Mat4Transformation(Mat4 *pOut, const Vec3 *scalingCenter, const Quaternion *scalingRot, 
   const Vec3 *scaling, const Vec3 *rotCenter, const Quaternion *rot, const Vec3 *trans) { 
      D3DXMatrixTransformation(pOut, scalingCenter, scalingRot, scaling, rotCenter, rot, trans);
}

void Mat4PerspectiveFovLH(Mat4 *pOut, float fovy, float aspect, float zn, float zf) { 
   D3DXMatrixPerspectiveFovLH(pOut, fovy, aspect, zn, zf); 
}
*/

/** Custom hashing algorithm:
  *
  * (1) Sum certain characters' int values
  * (2) Multiply sum by a decently large prime.
  * (3) sum each character again scaled by sum
  * (4) mod to make it fit in 32 bits
  */


#endif
