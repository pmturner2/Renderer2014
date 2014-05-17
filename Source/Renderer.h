#pragma once

/**
* Abstract class. Override with Graphics API-Specific child class.
*/
#include "stdafx.h"
#include "Renderable.h"
class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	virtual bool Init(HWND hWnd, HDC hdc) = 0;

	virtual void SetMultisample(UINT count, UINT quality) = 0;

	virtual void SetupScene(void) = 0;

	virtual void RenderScene(void) = 0;

	virtual void ReshapeWindow(int w, int h) { windowWidth = w; windowHeight = h; }
protected:
	int multisampleCount;
	int multisampleQuality;
	HDC hdc;
	float *clearColor; // r, g, b
	int windowWidth, windowHeight;
};

