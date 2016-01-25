#pragma once

#include <GL/glew.h>

#include "Mesh.h"

#include "Vector2f.h"

struct StaticMeshVertex {
	const float v_posx, v_posy, v_texelu, v_texelv;

	StaticMeshVertex(float p_x, float p_y, float t_u, float t_v);
	StaticMeshVertex(Vector2f pos, Vector2f texel);
};

class StaticMesh : public Mesh {

public:
	StaticMesh(MeshResource res);
	//~StaticMesh();

	void draw();

	static StaticMesh * load(const StaticMeshVertex *vertices, const GLuint v_length, const GLushort * indices, const GLuint i_length);

};