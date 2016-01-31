#version 430 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 tex;

uniform mat3 proj; 
out vec2 tex_coord;

void main() {
	gl_Position = vec4(proj * vec3(vPosition, 1), 1);
	tex_coord = tex;
}