#include "Renderable.h"

//----------------------------------------------------------------------------


Renderable::Renderable(void) : m_shader(0)
{

	// SIMD?

	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;

	scale[0] = 1.0f;
	scale[1] = 1.0f;
	scale[2] = 1.0f;

	rot[0] = 1.0f;
	rot[1] = 0.0f;
	rot[2] = 0.0f;
	rot[3] = 0.0f;

	m_shader = new Shader("SimpleVS.GLSL", "SimpleFS.GLSL");
	
	//modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.0f, -5.0f));
	modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	CreateSquare(1.0f);
}


//----------------------------------------------------------------------------

Renderable::~Renderable(void)
{
	if (m_shader != 0)
	{
		delete(m_shader);
		m_shader = 0;
	}
}

//----------------------------------------------------------------------------

void Renderable::CreateSquare(float side)
{
	float *verts = new float[18];
	float *colors = new float[18];
	float sideOver2 = side / 2.0f;

	for (int i = 0; i < 18; i++)
	{
		colors[i] = (float) std::rand() / (float) RAND_MAX;
	}

	verts[0] = -sideOver2;
	verts[1] = -sideOver2;
	verts[2] = 0.0f;

	verts[3] = -sideOver2;
	verts[4] = sideOver2;
	verts[5] = 0.0f;
	
	verts[6] = sideOver2;
	verts[7] = sideOver2;
	verts[8] = 0.0f;
		
	verts[9] = sideOver2;
	verts[10] = -sideOver2;
	verts[11] = 0.0f;
	
	verts[12] = -sideOver2;
	verts[13] = -sideOver2;
	verts[14] = 0.0f;
	
	verts[15] = sideOver2;
	verts[16] = sideOver2;
	verts[17] = 0.0f;

	glGenVertexArrays(1, &vaoId[0]);
	glBindVertexArray(vaoId[0]);

	glGenBuffers(2, vboId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verts, GL_STATIC_DRAW );

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors, GL_STATIC_DRAW );
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	delete[] verts;
	delete[] colors;
}

//----------------------------------------------------------------------------

void Renderable::StartRender(void)
{
	m_shader->Bind();
}

//----------------------------------------------------------------------------

void Renderable::Render(void)
{
	// TODO: bind outside of the individual (Batch)
	m_shader->Bind();
	
	int modelMatrixLocation = glGetUniformLocation(m_shader->Id(), "modelMatrix");
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
	
	glBindVertexArray(vaoId[0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glBindVertexArray(0);
	
	m_shader->Unbind();
}

//----------------------------------------------------------------------------

