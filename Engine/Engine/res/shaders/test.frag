#version 430 core

out vec4 fragColor;
//sample in vec3 col;
sample in vec2 tex_coord;

uniform sampler2D tex;

void main() {
	vec4 finalColor = texture(tex, tex_coord);
	fragColor = finalColor;
}