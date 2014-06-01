#pragma once
#include "boundingvolume.h"
class BoundingABB :
	public BoundingVolume
{
public:
	BoundingABB(void);
	~BoundingABB(void);

	void UpdateBoundingVolume(Mesh *m, mat4 &worldMatrix);
	void UpdateBoundingVolume(BoundingVolume *otherBV, mat4 &worldMatrix);
	
};

