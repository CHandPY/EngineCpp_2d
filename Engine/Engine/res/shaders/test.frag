#version 430 core

out vec4 fragColor;
sample in vec2 tex_coord;

layout (location = 5) uniform sampler2D tex0;
layout (location = 6) uniform sampler2D tex1;
layout (location = 7) uniform sampler2D tex2;
layout (location = 8) uniform sampler2D tex3;
layout (location = 9) uniform sampler2D look;

void main() {
	vec4 finalColor;
	vec4 lookup = texture(look, tex_coord);
	finalColor = mix(texture(tex1, tex_coord), texture(tex0, tex_coord), lookup.b);
	/*
	vec4 mx01 = mix(texture(tex0, tex_coord), texture(tex1, tex_coord), lookup.r); 
	vec4 mx_01_2 = mix(mx01, texture(tex2, tex_coord), lookup.g); 
	finalColor = mix(mx_01_2, texture(tex3, tex_coord), lookup.b);
	*/
	//vec4 mx01 =  mix(texture(tex0, tex_coord), texture(tex1, tex_coord), lookup.r);
	//vec4 mx23 =  mix(texture(tex2, tex_coord), texture(tex3, tex_coord), lookup.g);
	//finalColor = mix(mx01, mx23, lookup.b);
	fragColor = finalColor;
}