#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include<GL/glew.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	
	GLuint GetProgramID() const
	{
		return programID;
	}
	
	GLuint GetUniformLocation(const char* name) const;
	
	void Init();
	void AttachShader(GLuint shaderID);
	void Link();
	void Use();
	void Unuse();
	void Destroy();
	
	static GLuint CompileShader(GLenum type, const char* filename);
	
private:
	GLuint programID;
};

#endif //SHADER_PROGRAM_H