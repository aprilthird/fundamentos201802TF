#include "GLS_Program.h"
#include <fstream>
#include <vector>
#include <iostream>

#include "Error.h"

using namespace std;


GLS_Program::GLS_Program():programID(0), 
			fragmentVertextID(0),
			fragmentShaderID(0)
{
}


void GLS_Program::linkShader() {
	glAttachShader(programID, fragmentShaderID);
	glAttachShader(programID, fragmentVertextID);

	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLenght = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLenght);
		std::vector<GLchar> infoLog(maxLenght);
		glGetProgramInfoLog(programID, maxLenght, &maxLenght, &infoLog[0]);
		glDeleteProgram(programID);
		fatalError("Shaders could not be linked" + 
				printf("%s ", &(infoLog[0])));
		glDeleteShader(fragmentShaderID);
		glDeleteShader(fragmentVertextID);
		return;
	}
	glDetachShader(programID, fragmentShaderID);
	glDetachShader(programID, fragmentVertextID);
	glDeleteShader(fragmentShaderID);
	glDeleteShader(fragmentVertextID);



}


void GLS_Program::compileShaders(
	const string& vertextShaderFilePath,
	const string& fragmentShaderFilepath
) {


	programID = glCreateProgram();
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0) {
		fatalError("Fragment shader could not be initialized");
	}

	fragmentVertextID = glCreateShader(GL_VERTEX_SHADER);
	if (fragmentVertextID == 0) {
		fatalError("Vertex shader could not be initialized");
	}
	compileShader(vertextShaderFilePath, fragmentVertextID);
	compileShader(fragmentShaderFilepath, fragmentShaderID);
}

void GLS_Program::compileShader(
	const string& shaderPath, GLuint id) {

	string filecontent = "";
	string line = "";

	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError("Could not open " + shaderPath);
	}
	while (getline(shaderFile, line)) {
		filecontent += line + "\n";
	}
	shaderFile.close();

	const char* contents = filecontent.c_str();
	glShaderSource(id, 1, &contents, nullptr);
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std:vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

		std::cout << shaderPath << endl;
		fatalError("Shaders could not be compiled" +
			printf("%s ",&infoLog[0])
		);
		glDeleteShader(id);
		return;
	}


}

void GLS_Program::addAttribut(const string atributeName) {
	glBindAttribLocation(
		programID, numAttribute++, atributeName.c_str());
}

GLuint GLS_Program::getUniformLocation(const string& name) {
	GLuint location = glGetUniformLocation(programID, 
					name.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + name + " not found in shader");
	}
	return location;

}

void GLS_Program::use() {
	glUseProgram(programID);
	for (int i = 0; i < numAttribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLS_Program::unuse() {
	glUseProgram(programID);
	for (int i = 0; i < numAttribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}



GLS_Program::~GLS_Program()
{
}
