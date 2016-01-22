#pragma once

#include <GL/glew.h>

#define BUFFER_OFFSET(offset) ((void *)(offset))

struct MeshResource {
	GLuint m_vbo, m_ibo;
	//GLuint size;
	int TEMP_MID_SIZE;

	MeshResource(GLuint vbo, GLuint ibo);
};

class Mesh {

public:
	Mesh(MeshResource res);
	~Mesh();

	void draw(GLuint vbo, GLuint ibo);

	static MeshResource load(const GLfloat *vertices, const GLuint v_length, const GLfloat * texels, const GLuint t_length, const GLushort * indices, const GLuint i_length);

private:
	MeshResource m_res;

};