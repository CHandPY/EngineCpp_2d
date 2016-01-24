#include "Texture.h"

TextureResource::TextureResource(GLuint ID, GLenum target, GLuint width, GLuint height, GLuint depth) {
	i_ID = ID;
	i_target = target;
	i_width = width;
	i_height = height;
	i_depth = depth;
}

TextureResource::TextureResource() : TextureResource(0, 0, 0, 0, 0) { 
}

Texture::Texture(TextureResource res) {
	m_res = res;
}

Texture::~Texture() {
	
}

void Texture::bind(GLuint slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_res.i_target, m_res.i_ID);
}

TextureResource Texture::load(GLenum target, GLuint width, GLuint height, GLuint depth, GLenum min_filter, GLenum mag_filter, GLenum wrap_s, GLenum wrap_t, GLubyte * textureData) {
	GLuint ID;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	return TextureResource(ID, target, width, height, depth);
}

TextureResource Texture::load2D(GLuint width, GLuint height, GLenum min_filter, GLenum mag_filter, GLenum wrap_s, GLenum wrap_t, GLubyte * textureData) {
	return load(GL_TEXTURE_2D, width, height, 0, min_filter, mag_filter, wrap_s, wrap_t, textureData);
}

TextureResource Texture::load2D_nicest(GLuint width, GLuint height, GLubyte * textureData) {
	return load2D(width, height, GL_LINEAR, GL_LINEAR, GL_CLAMP, GL_CLAMP, textureData);
}

