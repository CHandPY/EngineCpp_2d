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

	void draw();

	static MeshResource load(float * vertices, int v_length, float * textels, int t_length, unsigned int * indices, int i_length);

private:
	MeshResource m_res;

};