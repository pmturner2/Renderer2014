
#pragma once
#include "Renderer.h"

#ifdef DX_11

class Renderer_DX11 : public Renderer
{
public:
	Renderer_DX11(void)
	{
		
	}
	~Renderer_DX11(void);

	bool Init(HWND hWnd, HDC hdc) override;
	void SetMultisample(UINT count, UINT quality) override;
};

#endif