#include "StaticMesh.h"

#include <iostream>

StaticMesh::StaticMesh(MeshResource res) : Mesh(res) {
}

//StaticMesh::~StaticMesh() : ~Mesh() {
//}

void StaticMesh::draw() {

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_res.m_vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(2 * sizeof(GLfloat)));
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
	// render mesh0s
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_res.m_ibo);
	glDrawElements(GL_TRIANGLES, m_res.m_size, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

StaticMesh * StaticMesh::load(const StaticMeshVertex *vertices, const GLuint v_length, const GLushort * indices, const GLuint i_length) {
	GLuint vbo, ibo;

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_length, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, v_length, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, v_length, vertices);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, v_length, vertices);
	//glBufferSubData(GL_ARRAY_BUFFER, v_length, t_length, texels);

	return new StaticMesh(MeshResource(vbo, ibo, i_length));
}

StaticMeshVertex::StaticMeshVertex(float p_x, float p_y, float t_u, float t_v) : v_posx(p_x), v_posy(p_y), v_texelu(t_u), v_texelv(t_v) {
}

StaticMeshVertex::StaticMeshVertex(Vector2f pos, Vector2f texel) : StaticMeshVertex(pos.getX(), pos.getY(), texel.getX(), texel.getY()) {
}
