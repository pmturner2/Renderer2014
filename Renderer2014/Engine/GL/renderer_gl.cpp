#include "Renderer_GL.h"

Logger m_logger;

void APIENTRY glDebug(GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​, void* userParam​)
{
	m_logger.Write((char *)message​);
}

#ifdef GL

//----------------------------------------------------------------------------

Renderer_GL::Renderer_GL(void)
{	
	clearColor = new float[3];
	SetClearColor(0.4f, 0.6f, 0.9f);
}

//----------------------------------------------------------------------------

Renderer_GL::~Renderer_GL(void)
{
	
	if (hglrc != NULL)
	{
		wglMakeCurrent (hdc, NULL);
		wglDeleteContext(hglrc);
	}
	if (clearColor)
	{
		delete clearColor;
		clearColor = 0;
	}
}

//----------------------------------------------------------------------------

void Renderer_GL::SetClearColor(float r, float g, float b)
{
	clearColor[0] = r;
	clearColor[1] = g;
	clearColor[2] = b;
}

//----------------------------------------------------------------------------
bool Renderer_GL::Init(HWND hWnd, HDC hdc)
{
	logger->Write("[OpenGL] Initializing OpenGL\n");
	this->hdc = hdc;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
    int pFormat = ChoosePixelFormat(hdc, &pfd); 
	if (pFormat == 0)
	{
		// Windows could not find a format for our needs.
		logger->Write("[OpenGL] Error choosing pixel Format\n");
		return false;
	}
    if (!SetPixelFormat(hdc, pFormat, &pfd))
	{
		// Our format was not valid
		logger->Write("[OpenGL] Error setting pixel Format\n");
		return false;
	}

	// Temporary OpenGL 2.1 Context used to springboard our 3.0+ Context
	HGLRC temp = wglCreateContext(hdc);
	wglMakeCurrent (hdc, temp);

	// Enable GLEW
	GLenum error =  glewInit();
	if (error != GLEW_OK)
	{
		
		// Can not init GLEW
		return false;
	}

	int attr[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		// Success, create new context and switch to it
		hglrc = wglCreateContextAttribsARB(hdc, NULL, attr);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(temp);
		wglMakeCurrent(hdc, hglrc);
	}
	else
	{
		// Our level not supported, Use temp 2.1 OpenGL
		hglrc = temp;
	}
#ifdef DEBUG
	glEnable(GL_DEBUG_OUTPUT);
#endif
	// Dump our GL Versions to verify
	int glVersion[2] = {-1, -1};
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
	
	char buffer [50];
	int bufferLen = sprintf (buffer, "[OpenGL] Successfully intialized OpenGL %d.%d\n",glVersion[0], glVersion[1]);
	//std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;
	logger->Write(buffer);
	renderable = new Renderable();	
	
	m_logger = *(this->logger);

	const GLvoid *userParam​;
	glDebugMessageCallback(glDebug, (const GLvoid *) userParam​);

	log_gl_params();
	// Success
	return true;
}

//----------------------------------------------------------------------------

void Renderer_GL::SetupScene(void)
{
	if (hglrc == NULL)
	{
		return;
	}

	// ClearColor	
	glClearColor(clearColor[0], clearColor[1], clearColor[2], 0.0f);

}

//----------------------------------------------------------------------------

void Renderer_GL::RenderScene(void)
{
	if (hglrc == NULL)
	{
		return;
	}
	viewMatrix = m_camera->GetViewMatrix();
	glViewport(0, 0, windowWidth, windowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	int shader_id = renderable->GetShaderId();
	if (shader_id < 1)
	{		
		return;
	}
	renderable->StartRender();
	
	// Pull location for matrices (Should store this per material)
	int projectionMatrixLocation = glGetUniformLocation(shader_id, "projectionMatrix");
	int viewMatrixLocation = glGetUniformLocation(shader_id, "viewMatrix");

	// Set current matrices (Projection = Per Scene, View = Per Frame, Model = Per Object)
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	
	renderable->Render();
	
	SwapBuffers(hdc);
}

//----------------------------------------------------------------------------

void Renderer_GL::SetProjectionMatrix(const float fov, const float nz, const float fz)
{	
	projectionMatrix = glm::perspective(fov, (const float) ((float)windowWidth / (float)windowHeight), nz, fz);
	viewMatrix = m_camera->GetViewMatrix();
	//viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f));
	//projectionMatrix = glm::perspective(60.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.f);

}

//----------------------------------------------------------------------------

void Renderer_GL::SetMultisample(UINT count, UINT quality)
{
}

//----------------------------------------------------------------------------
void Renderer_GL::ReshapeWindow(int w, int h)
{
	windowWidth = w;
	windowHeight = h;

	const float defaultFov = 60.0f;	
	const float defaultNear = 0.1f;
	const float defaultFar = 100.0f;
	
	SetProjectionMatrix(defaultFov, defaultNear, defaultFar);
}
//----------------------------------------------------------------------------

void Renderer_GL::log_gl_params () {
  GLenum params[] = {
    GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
    GL_MAX_CUBE_MAP_TEXTURE_SIZE,
    GL_MAX_DRAW_BUFFERS,
    GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
    GL_MAX_TEXTURE_IMAGE_UNITS,
    GL_MAX_TEXTURE_SIZE,
    GL_MAX_VARYING_FLOATS,
    GL_MAX_VERTEX_ATTRIBS,
    GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
    GL_MAX_VERTEX_UNIFORM_COMPONENTS,
    GL_MAX_VIEWPORT_DIMS,
    GL_STEREO,
  };
  const char* names[] = {
    "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
    "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
    "GL_MAX_DRAW_BUFFERS",
    "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
    "GL_MAX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_TEXTURE_SIZE",
    "GL_MAX_VARYING_FLOATS",
    "GL_MAX_VERTEX_ATTRIBS",
    "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
    "GL_MAX_VIEWPORT_DIMS",
    "GL_STEREO",
  };
  logger->Write ("GL Context Params:\n");
  char msg[256];
  // integers - only works if the order is 0-10 integer return types
  char buffer [50];
  for (int i = 0; i < 10; i++) {
    int v = 0;
    glGetIntegerv (params[i], &v);
	
	sprintf (buffer, "%s %i\n", names[i], v);
    logger->Write (buffer);
  }
  // others
  int v[2];
  v[0] = v[1] = 0;
  glGetIntegerv (params[10], v);
  sprintf (buffer, "%s %i %i\n", names[10], v[0], v[1]);
  logger->Write (buffer);

  unsigned char s = 0;
  glGetBooleanv (params[11], &s);
  sprintf (buffer, "%s %u\n", names[11], (unsigned int)s);
  logger->Write (buffer);
}


#endif
