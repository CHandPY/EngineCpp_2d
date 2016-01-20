#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>

#include "IO.h"

using namespace std;

#define SHADER_DIR_LOC			"res/shaders/"
#define SHADER_VERTEX			"vert"
#define SHADER_FRAGMENT			"frag"
#define SHADER_GEOMETRY			"geom"
#define SHADER_TESS_CNTRL		"tesc"
#define SHADER_TESS_EVAL		"tese"
#define SHADER_COMPUTE			"comp"

#define SHADER_PATH(name, type) string(SHADER_DIR_LOC + string(name) + "." + type).c_str()

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