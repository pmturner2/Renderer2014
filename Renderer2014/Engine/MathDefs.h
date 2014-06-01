

/** MathDefs.h - Header file for Vector/Matrix Math functions.  
 *  Peter Turner - Spring 2012
 *  Wrapped D3DX functions, to ease a transition to OpenGL or another Graphics API.
 */
#pragma once
#include "stdafx.h"

// String Hashing Function
extern UINT Hash(char *string);
extern UINT Hash(WCHAR *string);

#ifdef DX_11

#include <D3DX11.h>
//#include "d3dx10math.h"

// XNA Math For DX 11 (DX10 and DX9 used their own math library)
#include <xnamath.h>

/*
XMVECTOR is SIMD, but 16-byte aligned. 

1. Use XMVECTOR for local or global variables. 
2. Use XMFLOAT2, XMFLOAT3, and XMFLOAT4 for class data members. 
3. Use loading functions to convert from XMFLOAT* to XMVECTOR before doing calculations. 
4. Do calculations with XMVECTOR instances. 
5. Use storage functions to convert from XMVECTOR to XMFLOAT*.

// Loads XMFLOAT2 into XMVECTOR 
XMVECTOR XMLoadFloat2( CONST XMFLOAT2 *pSource);

// Loads 3-element UINT array into XMVECTOR 
XMVECTOR XMLoadInt3( CONST UINT* pSource); 

// Loads XMCOLOR into XMVECTOR 
XMVECTOR XMLoadColor( CONST XMCOLOR *pSource); 

// Loads XMBYTE4 into XMVECTOR 
XMVECTOR XMLoadByte4( CONST XMBYTE4 *pSource); 

We use the following methods to store data from XMVECTOR into XMFLOAT*: 

// Loads XMVECTOR into XMFLOAT2 
VOID XMStoreFloat2( XMFLOAT2 *pDestination, FXMVECTOR V); 

// Loads XMVECTOR into XMFLOAT3 
VOID XMStoreFloat3( XMFLOAT3 *pDestination, FXMVECTOR V); 

// Loads XMVECTOR into XMFLOAT4 
VOID XMStoreFloat4( XMFLOAT4 *pDestination, FXMVECTOR V);


PARAMETER PASSING:

// 32-bit Windows 
typedef const XMVECTOR FXMVECTOR; typedef const XMVECTOR& CXMVECTOR;

// 64-bit Windows 
typedef const XMVECTOR& FXMVECTOR; typedef const XMVECTOR& CXMVECTOR;

passing XMVECTOR parameters is as follows: The first 3 XMVECTOR parameters should be of type FXMVECTOR; any additional XMVECTOR parameters should be of type CXMVECTOR. Here is an example:


Constant XMVECTOR instances should use the XMVECTORF32 type.

XMVector3NearEqual - check if 2 vec3 are almost equal 

---


Just as we use XMFLOAT2 (2D), XMFLOAT3 (3D), and XMFLOAT4 (4D) when storing vectors in a class, it is recommended, by the XNA math documentation, to use the XMFLOAT4X4 type to store matrices as class data members.


More info at Source:
 Luna, Frank D. (2012-05-21). Introduction to 3D Game Programming with DirectX 11 (Kindle Locations 1238-1244). Mercury Learning and Information. Kindle Edition. 
*/


typedef XMVECTOR Vec2;
typedef XMVECTOR Vec3;
typedef XMVECTOR Vec4;
typedef XMMATRIX Mat4;
typedef XMVECTOR Quaternion;

typedef ID3D10ShaderResourceView Texture;
typedef ID3D10ShaderResourceView CubeMap;

typedef ID3D10Buffer VBuffer;
typedef ID3D10Buffer IBuffer;
/*
const float PI = (float) D3DX_PI;
const float PI_TIMES_2 = PI * 2.0f;
const float PI_OVER_2 =  PI * 0.5f;
const float PI_OVER_4 =  PI * 0.25f;

extern void Normalize(Vec2 *vIn, Vec2 *vOut);// { D3DXVec2Normalize(vIn, vOut); }
extern void Normalize(Vec3 *vIn, Vec3 *vOut);// { D3DXVec3Normalize(vIn, vOut); }
extern void Normalize(Vec4 *vIn, Vec4 *vOut);// { D3DXVec4Normalize(vIn, vOut); }
extern void Cross(Vec3 *pOut, Vec3 *pV1, Vec3 *pV2);// {   D3DXVec3Cross(pOut, pV1, pV2); }
extern float Dot(Vec3 *pV1, Vec3 *pV2);// {   return D3DXVec3Dot( pV1, pV2); }
extern float Length(const Vec2 *v);// { return D3DXVec2Length(v); }
extern float Length(const Vec3 *v);// { return D3DXVec3Length(v); }
extern float Length(const Vec4 *v);// { return D3DXVec4Length(v); }
extern void Mat4LookAtLH(Mat4 *pOut, const Vec3 *pEye, const Vec3 *pAt, const Vec3 *pUp);
extern void Mat4Identity(Mat4 *pOut);
extern void Mat4OrthoLH(Mat4 *pOut, float w, float h, float zn, float zf);
extern void Mat4Transformation(Mat4 *pOut, const Vec3 *scalingCenter, const Quaternion *scalingRot, 
   const Vec3 *scaling, const Vec3 *rotCenter, const Quaternion *rot, const Vec3 *trans);
extern void Mat4PerspectiveFovLH(Mat4 *pOut, float fovy, float aspect, float zn, float zf);  

*/
#endif
