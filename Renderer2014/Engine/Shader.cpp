#include "Shader.h"

//----------------------------------------------------------------------------

Shader::Shader(void)
{
}

//----------------------------------------------------------------------------

Shader::Shader(const char *vsFilename, const char *fsFilename)
{
	Init(vsFilename, fsFilename);
}

//----------------------------------------------------------------------------

Shader::~Shader(void)
{
	if (shader_id)
	{
#ifdef GL
		glDetachShader(shader_id, shader_fp);
		glDetachShader(shader_id, shader_vp);

		glDeleteShader(shader_fp);
		glDeleteShader(shader_vp);
		glDeleteProgram(shader_id);

		shader_id = 0;
#endif
	}

}


//----------------------------------------------------------------------------

#ifdef GL

void Shader::Init(const char *vsFilename, const char *fsFilename)
{
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

	char *vs_text = ReadFile(vsFilename);
	char *fs_text = ReadFile(fsFilename);

	if (vs_text != NULL && fs_text != NULL)
	{
		// Successfully read Shader files
		glShaderSource(shader_vp, 1, (const char **)&vs_text, 0);
		glShaderSource(shader_fp, 1, (const char **)&fs_text, 0);

		glCompileShader(shader_vp);
		glCompileShader(shader_fp);
	
		shader_id = glCreateProgram();
		glAttachShader(shader_id, shader_vp);
		glAttachShader(shader_id, shader_fp);
		glLinkProgram(shader_id);
	}

	// free memory allocated for fileread
	if (vs_text != NULL)
	{
		free(vs_text);
	}
	if (fs_text != NULL)
	{
		free(fs_text);
	}
	glBindAttribLocation(shader_id, 0, "in_Position");
	glBindAttribLocation(shader_id, 1, "in_Color");

}


//----------------------------------------------------------------------------

void Shader::Bind()
{
	glUseProgram(shader_id);
}

//----------------------------------------------------------------------------

void Shader::Unbind()
{
	glUseProgram(0);
}

#endif

//----------------------------------------------------------------------------

// helper: TODO: move to a utility class
char *Shader::ReadFile(const char *filename)
{
	char *returnText;

	FILE *fp = fopen(filename, "r");
	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		int count = ftell(fp);
		rewind(fp);
		if (count > 0)
		{
			returnText = (char *) malloc (sizeof(char) * (count + 1) );
			count = fread(returnText, sizeof(char), count, fp);
			returnText[count] = 0;
		}
		fclose(fp);
	}

	return returnText;
}