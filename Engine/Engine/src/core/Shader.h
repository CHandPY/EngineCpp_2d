#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>

// i changed somthing

using namespace std;

#define SHADER_DIR_LOC "C:\\"

class Shader {

public:
	Shader(GLuint program);
	~Shader();

	void use();

	static Shader* load(const char* name);
	static Shader* load(const char* vs_text, const char* fs_text);

private:
	GLuint  m_program;

};