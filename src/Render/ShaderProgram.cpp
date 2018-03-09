#include "ShaderProgram.h"

#include<fstream>
#include<vector>
#include<string>
#include<iostream>

ShaderProgram::ShaderProgram() :
	programID(0)
{
}

ShaderProgram::~ShaderProgram()
{
	Destroy();
}

GLuint ShaderProgram::GetUniformLocation(const char* name) const
{
	return glGetUniformLocation(programID, name);
}

void ShaderProgram::Init()
{
	programID = glCreateProgram();
}

void ShaderProgram::AttachShader(GLuint shaderID)
{
	glAttachShader(programID, shaderID);
}

void ShaderProgram::Link()
{
	glLinkProgram(programID);
	
	GLint infoLogLength = 0, result = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( GL_FALSE == result )
	{
		std::vector<char> ProgramErrorMessage( infoLogLength );
		glGetProgramInfoLog(programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
		
		char* aSzoveg = new char[ProgramErrorMessage.size()];
		memcpy( aSzoveg, &ProgramErrorMessage[0], ProgramErrorMessage.size());

		std::cerr << "[app.Init()] Sáder Huba panasza: " << aSzoveg << std::endl;

		delete aSzoveg;
	}
}

void ShaderProgram::Use()
{
	glUseProgram(programID);
}

void ShaderProgram::Unuse()
{
	glUseProgram(0);
}

void ShaderProgram::Destroy()
{
	if(programID != 0)
	{
		glDeleteProgram(programID);
	}
}

GLuint ShaderProgram::CompileShader(GLenum type, const char* filename)
{
	GLuint loadedShader = glCreateShader(type);
	if ( loadedShader == 0 )
	{
		std::cerr << "Couldn't Initialize shader (glCreateShader)!" << filename << std::endl;
		return 0;
	}
	
	std::ifstream shaderStream(filename);
	if (!shaderStream.is_open())
	{
		std::cerr << "Couldn't open shader file " << filename << std::endl;
		return 0;
	}
	
	//Copy the file to memory
	std::string shaderCode;
	shaderCode.assign(std::istreambuf_iterator<char>(shaderStream), std::istreambuf_iterator<char>());

	shaderStream.close();

	// Assign source to shader
	const char* sourcePointer = shaderCode.c_str();
	glShaderSource( loadedShader, 1, &sourcePointer, NULL );

	// Compile shader
	glCompileShader( loadedShader );

	// Get Compilation status
	GLint result = GL_FALSE;
    int infoLogLength;
	
	glGetShaderiv(loadedShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(loadedShader, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( GL_FALSE == result )
	{
		std::vector<char> VertexShaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(loadedShader, infoLogLength, NULL, &VertexShaderErrorMessage[0]);

		fprintf(stderr, "%s\n", &VertexShaderErrorMessage[0]);
	}

	return loadedShader;
}