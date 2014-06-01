// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

#include <iostream>
#include "Logger.h"
#include "MathDefs.h"
//#include <fbxsdk.h>
//#include "SkyObject.h"
// TODO: reference additional headers your program requires here


#ifdef GL

#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm/glm.hpp>
//#include <glm/gtc/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

typedef glm::mat4 mat4;
typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::quat quat;

typedef vec2 Vec2;
typedef vec3 Vec3;
typedef vec4 Vec4;

mat4 QuatToMat4(quat q);
vec3 Cross(vec3 &u, vec3 &v);
vec3 Normalize(vec3 v);
float Dot(vec3 u, vec3 v);

typedef vec3* VBuffer;
typedef short *IBuffer;

#endif