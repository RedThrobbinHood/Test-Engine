#pragma once

#include <string>
#include <GL\glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);	
	void linkShaders();
	void addAttribute(const std::string& attributeName);
	void Use();
	void unUse();
private:
	int _numAttributes;
	void compileShader(const std::string& filePath, GLuint id);

	// ID for entire program
	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

