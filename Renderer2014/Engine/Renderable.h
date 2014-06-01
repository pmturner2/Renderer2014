#include "stdafx.h"
#include "Shader.h"
#include "Mesh.h"
#include "TextureAsset.h"

#pragma once
class Renderable
{
public:
	Renderable(void);
	~Renderable(void);
	
	void Render();
	void StartRender();
	void CreateSquare(float side);
	unsigned int GetShaderId() { if (m_shader != 0) { return m_shader->Id(); } else { return 0; } }
private:
	// World Space Position
	float pos[3];
		
	float scale[3];
	
	// Quaternion
	float rot[4];

	// TODO: Replace shader with a material link
	Shader *m_shader;
	Mesh *m_mesh;
	TextureAsset *m_tex;
	glm::mat4 modelMatrix;

#ifdef GL
	unsigned int vaoId[1];
	unsigned int vboId[2]; // pos, color
#endif
};

