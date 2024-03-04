#include "Shader.h"

// Uniforms are set per draw; need to be setup before `glDrawElements` or `glDrawArrays`
// Attributes are set per vertex
// Here we are setting a uniform variable in our fragment shader
int Shader::getUniformLocation(const string &name) {
	int location {glGetUniformLocation(m_RendererID, name.c_str())};

	if (location == -1) {
		cout << "Warning: uniform '" << name << "' doesn't exist" << endl;
	}

	return location;
}

ShaderProgramSrc Shader::parseShader() {
	enum struct ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ifstream stream(m_FilePath);

	if (!stream.is_open()) {
		utilsFunctions::handleError(
			"Could not find shader source file: " +
			m_FilePath 
			// +
			// '\n' +
			// "Current working directory: " +
			// filesystem::current_path().string()
		);
	}

	string line;
	stringstream ss[2];
	ShaderType type {ShaderType::NONE};

	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos) {
				type = ShaderType::VERTEX;
			} else if (line.find("fragment") != string::npos) {
				type = ShaderType::FRAGMENT;
			}
		} else {
			ss[static_cast<int>(type)] << line << '\n';
		}
	}

	return {
		ss[0].str(),
		ss[1].str()
	};
}

// A shader is a program that runs on your GPU; we can create a vertext, geometry and fragment shader to override GPU defaults (or they may not exist)
// These shaders are compiled, linked and run on our GPU `glCompileShader`, whilst our C++ program runs on our CPU
// Vertex shader = transforms each vertex's 3D position in virtual space to the 2D coordinate on the screen (in a window)
	// and gets called for each vertex that is rendered
// Fragment (pixel) shader = defines RGBA (red, green, blue, alpha) colors for each pixel being processed
	// and gets called for each pixel that needs to get rasterized (process of drawing to screen, where a window is just a pixel array)
unsigned int Shader::createShaders(
	const string &vertexShaderSrc,
	const string &fragmentShaderSrc
) {
	unsigned int programId {glCreateProgram()};
	unsigned int vertexShaderId {compileShader(GL_VERTEX_SHADER, vertexShaderSrc)};
	unsigned int fragmentShaderId {compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc)};

	// Link shaders to a shader program
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glValidateProgram(programId);

	utilsFunctions::handleShaderProgramLinkError(programId, "Shader Program compilation failed");

	// Cleanup the generated shader intermediate .obj files from c++ compilation
	// Already stored inside the shader program and we no longer need them anymore
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}

unsigned int Shader::compileShader(
	unsigned int type,
	const string &shaderSrc
) {
	unsigned int shaderId {glCreateShader(type)};
	const char *cShaderSrc = shaderSrc.c_str();
	glShaderSource(shaderId, 1, &cShaderSrc, nullptr);
	glCompileShader(shaderId);
	string errMsg;

	switch (type) {
		case GL_VERTEX_SHADER:
			errMsg = "Vertex shader compilation failed";
			break;
		case GL_FRAGMENT_SHADER:
			errMsg = "Fragment shader compilation failed";
		default:
			errMsg = "Compilation failed";
	}

	utilsFunctions::handleShaderCompileError(shaderId, errMsg);

	return shaderId;
}

Shader::Shader(const string &filePath)
	: m_FilePath(filePath), m_RendererID(0)
{
	// The `.exe` file path will be the same regardless when executing debug or release
	// e.g. `build/Debug/FakeDoom.exe` or `build/Release/FakeDoom.exe`
	ShaderProgramSrc src {parseShader()};
	m_RendererID = createShaders(src.vertexSrc, src.fragmentSrc);
}

Shader::~Shader() {
	glDeleteProgram(m_RendererID);
}

void Shader::bind() const {
	glUseProgram(m_RendererID);
}

void Shader::unbind() const {
	glUseProgram(0);
}

void Shader::setUniform4f(
	const string &name,
	float v0,
	float v1,
	float v2,
	float v3
) {
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}