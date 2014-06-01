#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "BoundingVolume.h"
#include "BoundingABB.h"

//tODO: Replace with Material
#include "Shader.h"

#include <vector>
#include <algorithm>

class SceneNode
{
public:
	SceneNode(void);
	virtual ~SceneNode(void);

	// Adds a child, handles removal from old parent.
	void AddChild(SceneNode *child);

	// Remove Child from our list.
	void RemoveChild(SceneNode *child);

	SceneNode *GetParent() const { return m_parent; }
	void SetParent(SceneNode *newParent) { m_parent = newParent; }
	void SetUpdateBV(bool tf) { m_updateBV = tf; }

	void SetTranslation(vec3 pos);
	void SetRotation(quat q);
	void SetScale(float s);

	void Translate(vec3 offset);
	void Rotate(quat q);
	void Rotate(vec3 euler);
	void Rotate(float x, float y, float z);
	void Scale(float s);

	// TODO: Maybe extract out the BV to allow for different shapes
	void CalculateBoundingVolume();
	void CalculateLocalTransform();
	void CalculateWorldTransform(const mat4 *parentWorldTransform);
	
	// Per Frame
	void Update();
	void UpdateTransforms(const mat4 *parentWorldTransform,  bool forceUpdate);
	void UpdateBV();

	BoundingVolume *GetBV() const { return bv; }

	void SetName(char *newName) { name = newName; hashed_id = Hash(name); }
	SceneNode *FindNode(__int64 id);
protected:	
	char *name;
	__int64 hashed_id;

	std::vector<SceneNode *> m_children;
	
	SceneNode *m_parent;

	// Does not include Scale (apply these at the end)
	mat4 m_worldTransform;
	mat4 m_localTransform;

	// In Local Space
	vec3 m_position;
	quat m_rotation;

	// Not inheriting scale down the hierarchy. Applied separately. Uniform only.
	float m_scale; 
		
	//--- Bounding Sphere Information
	BoundingVolume *bv;
	
	//--- Render Information
	Mesh *m_mesh;
	Shader *m_shader;

	//--- State Stuff
	
	// Is this node (not hierarchy) currently enabled?
	// Check this when rendering / colliding
	bool m_enabled;
	
	// Has something changed that requires recalculating BV? 
	bool m_updateBV;

	// Has something changed that requires recalculating world and local transform matrices?
	bool m_updateLocalTransform;
private:
	// Copy Constructor Disabled
	SceneNode(const SceneNode &rhs);
	// Assignment Operator Disabled
	SceneNode operator = (SceneNode &rhs);
	
};

