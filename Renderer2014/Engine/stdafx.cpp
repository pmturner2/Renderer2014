// stdafx.cpp : source file that includes just the standard includes
// D3DGame.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

	mat4 QuatToMat4(quat q) { return glm::mat4_cast(q); }
	vec3 Cross(vec3 &u, vec3 &v) { return glm::cross( u, v) ; }
	vec3 Normalize(vec3 v) { return glm::normalize(v); }
	float Dot(vec3 u, vec3 v) { return u.x * v.x + u.y * v.y + u.z * v.z; }
