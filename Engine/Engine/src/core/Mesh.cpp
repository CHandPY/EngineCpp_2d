#include "Mesh.h"

MeshResource::MeshResource(GLuint vbo, GLuint ibo) {
	m_vbo = vbo;
	m_ibo = ibo;
}

#include <iostream>

Mesh::Mesh(MeshResource res) : m_res(res) {
}

Mesh::~Mesh() {
}

void Mesh::draw(GLuint vbo, GLuint ibo) {

	std::cout << m_res.m_ibo << " " << m_res.m_vbo << std::endl;

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_res.TEMP_MID_SIZE));
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
	// render mesh0s
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
}

MeshResource Mesh::load(float * vertices, int v_length, float * textels, int t_length, unsigned int * indices, int i_length) {
	GLuint vbo, ibo;
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_length, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, v_length + t_length, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, v_length, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, v_length, t_length, vertices);

	MeshResource m(vbo, ibo);
	m.TEMP_MID_SIZE = v_length;
	return m;
}
