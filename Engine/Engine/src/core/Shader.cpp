#include "Shader.h"

Shader::Shader(GLuint program) {
	m_program = program;
}

Shader::~Shader() {
	glDeleteProgram(m_program);
}

void Shader::use() {
	glUseProgram(m_program);
}

Shader * Shader::load(const char * name) {
	string vs_src, fs_src, line;
	cout << SHADER_DIR_LOC + string(name) + ".vs" << endl;
	ifstream vsf(SHADER_DIR_LOC + string(name) + ".vs"), fsf(SHADER_DIR_LOC + string(name) + ".fs");
	// Vertex shader
	if (vsf.is_open()) {
		while (getline(vsf, line)) {
			vs_src += line + "\n";
		}
		vsf.close();
	} else {
		cout << "Unable to open file for vertex shader" << endl;
		return nullptr;
	}
	// Fragment shader
	if (fsf.is_open()) {
		while (getline(fsf, line)) {
			fs_src += line + "\n";
		}
		fsf.close();
	} else {
		cout << "Unable to open file for vertex shader" << endl;
		return nullptr;
	}
	return load(vs_src.c_str(), fs_src.c_str());
}

Shader * Shader::load(const char * vs_text, const char * fs_text) {
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertShader, 1, &vs_text, NULL);
	glCompileShader(vertShader);

	glShaderSource(fragShader, 1, &fs_text, NULL);
	glCompileShader(fragShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return new Shader(program);
}
