#pragma once

#include <memory>

class Texture;

class FrameBuffer
{
public:
	FrameBuffer(size_t width, size_t height);

	~FrameBuffer();

	void attachTexture(const std::shared_ptr<Texture>& tex);

	// Sets OpenGL up to render to this FBO
	void setupRender();

	// Restores OpenGL rendering to the main frame buffer
	void cleanupRender();

private:
	size_t width;
	size_t height;
	unsigned int fbo;
	unsigned int depthBuff;
};
