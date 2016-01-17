#include "Shader.h"

Shader::Shader(GLuint program) {
	m_program = program;
}

/* CHANGE LATER TO NO DELET ON ~ */
Shader::~Shader() {
	glDeleteProgram(m_program);
}

void Shader::use() {
	glUseProgram(m_program);
}

Shader * Shader::load(const char * name) {
	int vsl;
	string* vsa = IO::load(string(SHADER_DIR_LOC + string(name) + ".vs").c_str(), &vsl);
	string vs = "";
	for (int i = 0; i < vsl; i++)
		vs += vsa[i];
	int fsl;
	string* fsa = IO::load(string(SHADER_DIR_LOC + string(name) + ".fs").c_str(), &fsl);
	string fs = "";
	for (int i = 0; i < fsl; i++)
		fs += fsa[i];
	return load(vs.c_str(), fs.c_str());
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
