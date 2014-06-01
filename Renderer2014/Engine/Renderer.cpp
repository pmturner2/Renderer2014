#include "Renderer.h"


Renderer::Renderer(void)
{
	m_camera = new Camera();
}

//----------------------------------------------------------------------------


Renderer::~Renderer(void)
{
	if (m_camera != 0)
	{
		delete(m_camera);
	}
}

//----------------------------------------------------------------------------

void Renderer::Update(float dt)
{
	//logger->Write("Renderer::Update");
	if (m_camera != 0)
	{
		//logger->Write("renderer updating camera");
		m_camera->Update(dt);
	}
}

//----------------------------------------------------------------------------
