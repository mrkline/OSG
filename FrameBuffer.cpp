#include "StdAfx.hpp"
#include "FrameBuffer.hpp"

#include "Exceptions.hpp"
#include "GLErrors.hpp"
#include "Texture.hpp"

using namespace std;

FrameBuffer::FrameBuffer(size_t width, size_t height)
	: width(width), height(height)
{
	glGenFramebuffers(1, &fbo);
	throwGLExceptions(__FUNCTION__);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Generate depth buffer and bind it to the FBO
	glGenRenderbuffers(1, &depthBuff);
	throwGLExceptions(__FUNCTION__);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuff);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	throwGLExceptions(__FUNCTION__);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
	                          GL_RENDERBUFFER, depthBuff);
	throwGLExceptions(__FUNCTION__);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteRenderbuffers(1, &depthBuff);
	glDeleteFramebuffers(1, &fbo);
}

void FrameBuffer::attachTexture(const shared_ptr<Texture>& tex)
{
	if (tex->getWidth() != width || tex->getHeight() != height) {
		throw Exceptions::ArgumentException("A texture must be the same"
		                                    " dimensions as the FBO to be"
		                                    " attached to it.",
		                                    __FUNCTION__);
	}
	// Bind the texture to the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
	                       tex->getID(), 0);
	throwGLExceptions(__FUNCTION__);
	// Check to make sure we're good to go
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw Exceptions::GLException("Frame buffer object is not complete.",
		                            __FUNCTION__);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::setupRender()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	throwGLExceptions(__FUNCTION__);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0, 0, width, height);
}

void FrameBuffer::cleanupRender()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	throwGLExceptions(__FUNCTION__);
	glPopAttrib();
}
