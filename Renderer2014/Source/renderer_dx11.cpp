#include "Renderer_DX11.h"

#ifdef DX_11

Renderer_DX11::Renderer_DX11(void)
{
}

//----------------------------------------------------------------------------

Renderer_DX11::~Renderer_DX11(void)
{
}

//----------------------------------------------------------------------------

bool Renderer_DX11::Init(HWND hWnd, HDC hdc)
{

}

//----------------------------------------------------------------------------

void Renderer_DX11::SetMultisample(UINT count, UINT quality)
{
	
	// Clamp Sample Count to appropriate Range.
	if (count > D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT)
	{
		this->multisampleCount = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
	}
	else if (count < 1)
	{
		this->multisampleCount = 1;
	}
	else
	{
		this->multisampleCount = count;
	}

	int maxQuality = 0;

	this->multisampleQuality = quality;
}

#endif