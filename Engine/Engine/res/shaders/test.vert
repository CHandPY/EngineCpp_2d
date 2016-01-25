#version 430 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 tex;

uniform mat3 proj; 
//out vec3 col;
out vec2 tex_coord;

void main() {
	//normalize(color.xzy * color.zyx);
	gl_Position = vec4(proj * vec3(vPosition, 1), 1);
	//col = vec3(tex, 1);// mix(color, vec3(1, 1, 1), vec3(.08, .12, .0));//sin(pow(mix(vec3(1, 1, 1), color, vec3(.5, .5, .5)), vec3(vPosition, 1)));
	tex_coord = tex;
}