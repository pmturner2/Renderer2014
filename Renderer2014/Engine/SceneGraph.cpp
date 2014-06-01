#include "SceneGraph.h"


SceneGraph::SceneGraph(void) : root(0), id_count(0)
{
	root = new SceneNode();
	root->SetParent(0);
}

//----------------------------------------------------------------------------

SceneGraph::~SceneGraph(void)
{
	delete root;
}

//----------------------------------------------------------------------------

SceneNode *SceneGraph::FindNode(char *name)
{
	__int64 target_id = Hash(name);
	if (root == 0)
	{
		return 0;
	}
	return root->FindNode(target_id);
}

//----------------------------------------------------------------------------

SceneNode *SceneGraph::AddNewNode(SceneNode *parentNode, char *name = 0)
{
	SceneNode *newNode = new SceneNode();
	char newName[40];

	if (name == 0)
	{		
		sprintf(newName, "SceneObject_%d", id_count++);
	}
	else
	{
		if (strlen(name) > 31)
		{
			name[32] = 0;
		}
		sprintf(newName, "%s_%d", name, id_count++);
	}

	newNode->SetName(newName);
	if(parentNode != 0)
	{
		parentNode->AddChild(newNode);
	}
	else
	{
		root->AddChild(newNode);
	}
	return newNode;
}

//----------------------------------------------------------------------------

SceneNode *SceneGraph::AddNode(SceneNode *parentNode, SceneNode *newNode)
{
	if (parentNode != 0)
	{
		parentNode->AddChild(newNode);
	}
	else
	{
		root->AddChild(newNode);
	}
	return newNode;
}

//----------------------------------------------------------------------------

void SceneGraph::Update()
{
	if (root != 0)
	{
		root->UpdateTransforms(0, false);
		root->UpdateBV();
	}
}
//----------------------------------------------------------------------------
