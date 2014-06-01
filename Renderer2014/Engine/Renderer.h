#pragma once

/**
* Abstract class. Override with Graphics API-Specific child class.
*/
#include "stdafx.h"
#include "Renderable.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);

	void SetLogger(Logger *l) { logger = l; }

	virtual bool Init(HWND hWnd, HDC hdc) = 0;

	virtual void SetMultisample(UINT count, UINT quality) = 0;

	virtual void SetupScene(void) = 0;

	virtual void RenderScene(void) = 0;

	virtual void ReshapeWindow(int w, int h) { windowWidth = w; windowHeight = h; }
	virtual void Update(float dt);
	Camera *GetCamera() const { return m_camera; }
	
	int GetWindowWidth() const { return windowWidth; }
	int GetWindowHeight() const { return windowHeight; }
protected:
	int multisampleCount;
	int multisampleQuality;
	HDC hdc;
	float *clearColor; // r, g, b

	int windowWidth, windowHeight;

	Logger *logger;

	Camera *m_camera;

	
};

