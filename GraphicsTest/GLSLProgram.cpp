#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

//Code handles GLSL shading language for OpenGL


// Initialize variables on GLSL contructor to save copies from being made
GLSLProgram::GLSLProgram() : _numAttributes(0),_programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{

}


GLSLProgram::~GLSLProgram()
{

}

// Opens shader files through given path, reads data and compile shaders 
void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	// Get the program object
	_programID = glCreateProgram();

	// Create shader for each shadertype and check for fatal errors
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("Vert shader failed to be created!");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("Frag shader failed to be created!");
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
	
}

void GLSLProgram::linkShaders()
{
	
	// Attatch shader to program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// Link program
	glLinkProgram(_programID);

	// Link fail check
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		// Program/shaders not needed
		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		//Log error
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shaders failed to link!");

		return;
	}

	// Detach shader after successful link
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);

	// Delete shader IDs to free up resources
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);


}

// Adds attribute then increment num of attributes
void GLSLProgram::addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(_programID, _numAttributes, attributeName.c_str());
	_numAttributes++;
}

// Gets the uniform for the shader
GLuint GLSLProgram::getUniformLocation(const std::string& uniformName) {
	GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + uniformName + " NOT FOUND IN SHADER!");
	}

	return location;
}


void GLSLProgram::Use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unUse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
{
	// Grab vertex file from path
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		perror(filePath.c_str());
		fatalError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	// Run while getline returns positive num
	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}

	vertexFile.close();

	// Pass the shader data
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	// Compile vertex shader
	glCompileShader(id);

	//Check for success
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//Adds to error log
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Exit with failure and dont leak shader
		glDeleteShader(id);

		// Print errors
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader " + filePath + " failed to compile");
	}
}
