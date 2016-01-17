#version 430 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec3 color;

uniform mat3 proj; 
out vec3 col;

void main() {
	col = color;
	gl_Position = vec4(proj * vec3(vPosition, 0), 1);
}