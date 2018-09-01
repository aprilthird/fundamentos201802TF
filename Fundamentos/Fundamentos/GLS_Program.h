#pragma once

#include <GL/glew.h>
#include <string>

using namespace std;

class GLS_Program
{
private:
	GLuint programID;
	GLuint fragmentShaderID;
	GLuint fragmentVertextID;

	void compileShader(const string& shaderPath,GLuint uid);
public:
	GLS_Program();
	int numAttribute;
	void addAttribut(const string atributeName);
	void use();
	void unuse();
	void compileShaders(const string& vertexShaderFilePath,
		const string& fragmentShaderFilePath
	);
	GLuint getUniformLocation(const string& name);
	void linkShader();
	~GLS_Program();
};

