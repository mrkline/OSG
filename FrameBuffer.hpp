#pragma once

#include <memory>

class Texture;

//! A wrapper around OpenGL's framebuffer objects
class FrameBuffer
{
public:
	FrameBuffer(size_t width, size_t height);

	~FrameBuffer();

	//! Attaches a texture for use as a render target
	void attachTexture(const std::shared_ptr<Texture>& tex, int rtNum = 0);

	//! Sets the number of expected render targets. The default is 1
	void setNumRenderTargets(size_t num);

	//! Sets OpenGL up to render to this FBO
	void setupRender();

	//! Restores OpenGL rendering to the main frame buffer
	void cleanupRender();

private:
	size_t width;
	size_t height;
	unsigned int fbo;
	unsigned int depthBuff;
};
