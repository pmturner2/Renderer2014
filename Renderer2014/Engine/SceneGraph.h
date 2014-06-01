#pragma once
#include "stdafx.h"
#include "SceneNode.h"

class SceneGraph
{
public:
	SceneGraph(void);
	~SceneGraph(void);
	void Update();
	SceneNode *AddNewNode(SceneNode *parentNode, char *name);
	SceneNode *AddNode(SceneNode *parentNode, SceneNode *newNode);
	SceneNode *FindNode(char *name);
private:
	SceneNode *root;
	int id_count;
};

