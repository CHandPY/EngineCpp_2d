#pragma once

#include <GL/glew.h>

struct TextureResource {
	GLuint i_ID;
	GLuint i_width, i_height, i_depth;
	GLenum i_target;

	TextureResource(GLuint ID, GLenum target, GLuint width, GLuint height, GLuint depth);
	TextureResource();
};

class Texture {

public:
	Texture(TextureResource res);
	~Texture();

	void bind(GLuint slot);

	static TextureResource load(GLenum target, GLuint width, GLuint height, GLuint depth, GLenum min_filter, GLenum mag_filter, GLenum wrap_s, GLenum wrap_t, GLubyte *textureData);
	static TextureResource load2D(GLuint width, GLuint height, GLenum min_filter, GLenum mag_filter, GLenum wrap_s, GLenum wrap_t, GLubyte *textureData);
	static TextureResource load2D_nicest(GLuint width, GLuint height, GLubyte *textureData);

private:
	TextureResource m_res;
};