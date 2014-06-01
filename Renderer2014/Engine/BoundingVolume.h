#pragma once
#include "stdafx.h"
#include "mesh.h"

class BoundingVolume
{
public:
	BoundingVolume(void);
	virtual ~BoundingVolume(void) = 0;

	virtual void UpdateBoundingVolume(Mesh *m, mat4 &worldMatrix) = 0;
	virtual void UpdateBoundingVolume(BoundingVolume *otherBV, mat4 &worldMatrix) = 0;
	
	virtual void ResetVolume() { m_worldMin = vec3(0); m_worldMax = vec3(0); }

	void GetWorldExtents(vec3 &outWorldMin, vec3 &outWorldMax) { outWorldMin = m_worldMin; outWorldMax = m_worldMax; }
protected:
	
	vec3 m_worldMin;
	vec3 m_worldMax;
};

