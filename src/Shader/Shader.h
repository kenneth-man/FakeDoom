#ifndef _SHADER_
#define _SHADER_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "../utils/functions/functions.h"

using namespace std;

struct ShaderProgramSrc {
	string vertexSrc;
	string fragmentSrc;
};

class Shader {
private:
	string m_FilePath;
	unsigned int m_RendererID;
	unordered_map<string, int> m_UniformLocationCache;

	int getUniformLocation(const string &name);
	ShaderProgramSrc parseShader();
	unsigned int createShaders(const string &vertexShaderSrc, const string &fragmentShaderSrc);
	unsigned int compileShader(unsigned int type, const string &shaderSrc);
public:
	Shader(const string &filePath);
	~Shader();

	void bind() const;
	void unbind() const;
	void setUniform1i(const string &name, int value);
	void setUniform1f(const string &name, float value);
	void setUniform4f(const string &name, float v0, float v1, float v2, float v3);
};

#endif