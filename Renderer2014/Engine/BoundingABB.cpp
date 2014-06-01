#include "BoundingABB.h"


BoundingABB::BoundingABB(void)
{
}


BoundingABB::~BoundingABB(void)
{
}

void BoundingABB::UpdateBoundingVolume(Mesh *m, mat4 &worldMatrix)
{
	vec3 meshLocalMin;
	vec3 meshLocalMax;

	vec4 meshWorldMin4;
	vec4 meshWorldMax4;

	vec3 meshWorldMin;
	vec3 meshWorldMax;

	if (m != 0)
	{
		m->GetLocalExtents(meshLocalMin, meshLocalMax);
		meshWorldMin4 = worldMatrix * vec4(meshLocalMin, 1);
		meshWorldMax4 = worldMatrix * vec4(meshLocalMax, 1);
		meshWorldMin = (Vec3) meshWorldMin4;
		meshWorldMax = (Vec3) meshWorldMax4;

		if (meshWorldMin.x < this->m_worldMin.x)
		{
			this->m_worldMin.x = meshWorldMin.x;
		}
		else if (meshWorldMax.x > this->m_worldMax.x)
		{
			this->m_worldMax.x = meshWorldMax.x;
		}

		if (meshWorldMin.y < this->m_worldMin.y)
		{
			this->m_worldMin.y = meshWorldMin.y;
		}
		else if (meshWorldMax.y > this->m_worldMax.y)
		{
			this->m_worldMax.y = meshWorldMax.y;
		}

		if (meshWorldMin.z < this->m_worldMin.z)
		{
			this->m_worldMin.z = meshWorldMin.z;
		}
		else if (meshWorldMax.z > this->m_worldMax.z)
		{
			this->m_worldMax.z = meshWorldMax.z;
		}
	}
}

void BoundingABB::UpdateBoundingVolume(BoundingVolume *otherBV, mat4 &worldMatrix)
{
	if (otherBV != 0)
	{
		vec3 otherWorldMin;
		vec3 otherWorldMax;
		otherBV->GetWorldExtents(otherWorldMin, otherWorldMax);

		if (otherWorldMin.x < this->m_worldMin.x)
		{
			this->m_worldMin.x = otherWorldMin.x;
		}
		else if (otherWorldMax.x > this->m_worldMax.x)
		{
			this->m_worldMax.x = otherWorldMax.x;
		}

		if (otherWorldMin.y < this->m_worldMin.y)
		{
			this->m_worldMin.y = otherWorldMin.y;
		}
		else if (otherWorldMax.y > this->m_worldMax.y)
		{
			this->m_worldMax.y = otherWorldMax.y;
		}

		if (otherWorldMin.z < this->m_worldMin.z)
		{
			this->m_worldMin.z = otherWorldMin.z;
		}
		else if (otherWorldMax.z > this->m_worldMax.z)
		{
			this->m_worldMax.z = otherWorldMax.z;
		}
	}
}