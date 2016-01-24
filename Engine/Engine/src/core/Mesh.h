#pragma once

#include <GL/glew.h>

#define BUFFER_OFFSET(offset) ((void *)(offset))

struct MeshResource {
	GLuint m_vbo, m_ibo, m_size;
	
	MeshResource(GLuint vbo, GLuint ibo, GLuint size) : m_vbo(vbo), m_ibo(ibo), m_size(size) {};
	MeshResource() : MeshResource(0, 0, 0) {};
};

class Mesh {

public:
	Mesh(MeshResource res) : m_res(res) {};
	//virtual ~Mesh() = 0;

	virtual void draw() = 0;

protected:
	MeshResource m_res;

};