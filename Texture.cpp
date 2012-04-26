#include "StdAfx.hpp"
#include "Texture.hpp"

#include "Exceptions.hpp"
#include "GLErrors.hpp"

Texture::Texture(const char* filename, GLenum format, bool mipmaps)
	: hasMipmaps(mipmaps)
{
	using namespace SILLY;
	// Light up SILLY and load our image
	SILLYInit();
	// Load data from file name
	FileDataSource src(filename);
	Image img(src);
	if (!img.loadImageHeader()) {
		throw Exceptions::IOException("Error loading image header",
		                              __FUNCTION__);
	}
	else  {
		// Determine what format we should use
		PixelFormat pf;
		switch (format) {
		case GL_RGB:
			pf = PF_RGB;
			break;
		case GL_RGBA:
			pf = PF_RGBA;
			break;
		default:
			throw Exceptions::ArgumentException("SILLY can only load"
			                                    "RGB or RGBA",
			                                    __FUNCTION__);
		}
		if (!img.loadImageData(pf)) {
			throw Exceptions::IOException("Error loding image data",
			                              __FUNCTION__);
		}
		else {
			init(img.getPixelsDataPtr(), format == GL_RGB ? 3 : 4,
			     img.getWidth(), img.getHeight(),
			     format, GL_UNSIGNED_BYTE, mipmaps);
		}
	}
}

Texture::Texture(const void* data, int colorComponents,
                 size_t width, size_t height,
                 GLenum format, GLenum type, bool mipmaps)
	: hasMipmaps(mipmaps)
{
	// Light up SILLY
	SILLY::SILLYInit();
	init(data, colorComponents, width, height, format, type, mipmaps);
}

Texture::~Texture()
{
	// Shut SILLY down
	glDeleteTextures(1, &id);
	SILLY::SILLYCleanup();
}

void Texture::setAsActiveTexture()
{
	// Bind the texture and set its parameters
	glBindTexture(GL_TEXTURE_2D, id);
	for (auto it = intParams.begin(); it != intParams.end(); ++it)
		glTexParameteri(GL_TEXTURE_2D, it->first, it->second);

	for (auto it = floatParams.begin(); it != floatParams.end(); ++it)
		glTexParameterf(GL_TEXTURE_2D, it->first, it->second);
}

void Texture::init(const void* data, int colorComponents,
                   size_t width, size_t height,
                   GLenum format, GLenum type, bool mipmaps)
{
	this->width = width;
	this->height = height;
	glGenTextures(1, &id);
	throwGLExceptions(__FUNCTION__);
	glBindTexture(GL_TEXTURE_2D, id);
	// select modulate to mix texture with color for shading
	// Likely not needed since we plan on using shaders for everything
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	intParams[GL_TEXTURE_MIN_FILTER] = GL_LINEAR_MIPMAP_NEAREST;
	intParams[GL_TEXTURE_MIN_FILTER] = GL_LINEAR;
	// Clamp texture coordinates by default
	intParams[GL_TEXTURE_WRAP_S] = GL_CLAMP;
	intParams[GL_TEXTURE_WRAP_T] = GL_CLAMP;

	if (mipmaps) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, colorComponents, width, height,
		                  format, type, data);
		throwGLExceptions(__FUNCTION__);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, colorComponents, width, height,
		             0, format, type, data);
		throwGLExceptions(__FUNCTION__);
	}
}
