#version 430 core

out vec4 fragColor;
sample in vec3 col;

void main() {
	fragColor = vec4(col, 1.0);
}