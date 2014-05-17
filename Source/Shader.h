
#pragma once

#include "stdafx.h"

#ifdef GL

#include <GL/glew.h>
#include <GL/wglew.h>

#endif

class Shader
{
public:
	Shader(void);
	Shader(const char *vsFilename, const char *fsFilename);

	~Shader(void);

	void Init(const char *vsFilename, const char *fsFilename);
	void Bind();
	void Unbind();
	unsigned int Id() { return shader_id; }
private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;

	char *ReadFile(const char *filename);
};
