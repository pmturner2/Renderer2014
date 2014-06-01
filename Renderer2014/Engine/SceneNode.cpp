#include "SceneNode.h"


SceneNode::SceneNode(void) : m_position(vec3(0)), m_parent(0), m_scale(1), m_enabled(true)
{
	bv = new BoundingABB();
}

//----------------------------------------------------------------------------

SceneNode::~SceneNode(void)
{
	for (std::vector<SceneNode*>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		delete *itr;
	}

	/*
	std::vector<SceneNode*>::iterator itr = m_children.begin();
	while(itr != m_children.end())
	{
		delete *itr;
		++itr;
	}
	*/
	if (bv)
	{
		delete bv;
	}
}

//----------------------------------------------------------------------------

void SceneNode::AddChild(SceneNode *child) 
{ 
	SceneNode *oldParent = child->GetParent();
	if (oldParent != 0)
	{
		oldParent->RemoveChild(child);
	}
	m_children.push_back(child);
	child->SetParent(this);
}

//----------------------------------------------------------------------------

void SceneNode::RemoveChild(SceneNode *child) 
{ 
	m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
	child->SetParent(0);
}

//----------------------------------------------------------------------------


// This is assumed to be Local Space
// TODO: Add World Space Version
void SceneNode::SetTranslation(vec3 pos)
{
	this->m_position = pos;

	// Update these during our update loop
	this->m_updateLocalTransform = true;
	this->m_updateBV = true;
}

//----------------------------------------------------------------------------

// This is assumed to be Local Space
// TODO: Add World Space Version
void SceneNode::SetRotation(quat q)
{
	this->m_rotation = q;

	// Update these during our update loop
	this->m_updateLocalTransform = true;
	
	this->m_updateBV = true;
}

//----------------------------------------------------------------------------

// Scale is not inherited down the hierarchy, so this is world / local space
void SceneNode::SetScale(float s)
{
	this->m_scale = s;

	// Update these during our update loop
	this->m_updateLocalTransform = true;
	this->m_updateBV = true;
}

//----------------------------------------------------------------------------

void SceneNode::Translate(vec3 offset)
{
	// Assumed World Space
	this->m_position += offset;

	// Update these during our update loop
	this->m_updateLocalTransform = true;
	this->m_updateBV = true;
}

//----------------------------------------------------------------------------

void SceneNode::Rotate(quat q)
{
	// Assumed World Space
	this->m_rotation *= q;

	// Update these during our update loop
	this->m_updateLocalTransform = true;
	this->m_updateBV = true;
}

//----------------------------------------------------------------------------

void SceneNode::Rotate(vec3 euler)
{
	Rotate(quat(euler));
}

//----------------------------------------------------------------------------

void SceneNode::Rotate(float x, float y, float z)
{
	Rotate(quat(vec3(x, y, z)));
}

//----------------------------------------------------------------------------

void SceneNode::CalculateWorldTransform(const mat4 *parentWorldTransform)
{
	if (this->m_updateLocalTransform)
	{
		CalculateLocalTransform();
	}

	if (parentWorldTransform == 0)
	{
		this->m_worldTransform = this->m_localTransform;
	}
	else
	{
		// Concatenate Parent and Local
		this->m_worldTransform = *parentWorldTransform * this->m_localTransform;
	}
}

//----------------------------------------------------------------------------

void SceneNode::CalculateLocalTransform()
{
	if (this->m_updateLocalTransform)
	{	
		this->m_localTransform = QuatToMat4(m_rotation);
		
		this->m_localTransform[0][3] = this->m_position[0];
		this->m_localTransform[1][3] = this->m_position[1];
		this->m_localTransform[2][3] = this->m_position[2];
		this->m_localTransform[3][3] = 1;
		
		this->m_updateLocalTransform = false;
	}
}

//----------------------------------------------------------------------------

void SceneNode::CalculateBoundingVolume()
{	
	if (this->m_updateBV)
	{		
		bv->ResetVolume();

		bv->UpdateBoundingVolume(this->m_mesh, this->m_worldTransform);

		for (std::vector<SceneNode*>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
		{
			bv->UpdateBoundingVolume((*itr)->GetBV(), this->m_worldTransform);
		}

		
		this->m_updateBV = false;
	}
}

//----------------------------------------------------------------------------

void SceneNode::Update()
{
}

//----------------------------------------------------------------------------

void SceneNode::UpdateTransforms(const mat4 *parentWorldTransform, bool forceUpdate = false)
{
	// if we need to update our local Transform Matrix, do so
	if (this->m_updateLocalTransform)
	{
		CalculateLocalTransform();
	}

	// if our local trasnform matrix has changed OR our parent has changed, update our world Transform
	if (this->m_updateLocalTransform || forceUpdate)
	{
		CalculateWorldTransform(parentWorldTransform);
	}
	for (std::vector<SceneNode*>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		// Update our children, forcing if we were forced or if we are updated
		(*itr)->UpdateTransforms(&(this->m_worldTransform), (this->m_updateLocalTransform || forceUpdate));
	}	
}

//----------------------------------------------------------------------------

void SceneNode::UpdateBV()
{
	for (std::vector<SceneNode*>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		// Update our children, forcing if we were forced or if we are updated
		(*itr)->UpdateBV();
	}
	
	if (this->m_updateBV)
	{
		CalculateBoundingVolume();
		
		// Pass back up the hierarchy
		this->m_parent->SetUpdateBV(true);
	}		
}

//----------------------------------------------------------------------------

SceneNode *SceneNode::FindNode(__int64 id)
{
	if (hashed_id == id)
	{
		return this;
	}

	
	// Foreach Child, DFS
	for (std::vector<SceneNode*>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		SceneNode *result = ( (*itr)->FindNode(id));
		if (result != 0)
		{
			return result;
		}
	}

}

//----------------------------------------------------------------------------
