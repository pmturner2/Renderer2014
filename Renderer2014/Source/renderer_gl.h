
#pragma once
#include "renderer.h"

#ifdef GL

#include <GL/glew.h>
#include <GL/wglew.h>

class Renderer_GL :	public Renderer
{
public:
	Renderer_GL(void);
	~Renderer_GL(void);
	bool Init(HWND hWnd, HDC hdc) override;	
	void SetMultisample(UINT count, UINT quality) override;
	void SetupScene(void) override;	
	void RenderScene(void) override;
	void SetClearColor(float r, float g, float b);
	void SetProjectionMatrix(float fov, float near, float far);
	void ReshapeWindow(int w, int h) override;
	
private:
	
	HGLRC hglrc;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	
	Renderable *renderable;
	
};

#endif