#pragma once

#include <map>
#include <string>

//! Represents a 2D texture loaded into OpenGL
class Texture
{
public:
	/*!
	 * \brief Loads a texture from a PNG, JPEG, or TGA using CEGUI's SILLY
	 * \param filename The name of the file to load as a texture
	 * \param format The desired texture format. Must be GL_RGB or GL_RGBA
	 * \param mipmaps true to generate mipmaps
	 */
	Texture(const char* filename, GLenum format = GL_RGBA, bool mipmaps = true);

	/*!
	 * \brief Loads a texture directly from memory
	 * \param data A pointer to the texture data. Pass null in order to create a
	 *             blank texture (e.g. for Render To Texture)
	 * \param colorComponents The number of color channels the texture contains
	 * \param width The width of the texture, in pixels
	 * \param height The height of the texture, in pixels
	 * \param format The Desired texture format
	 * \param type The variable type of the data (GL_BYTE, GL_SHORT, etc.)
	 * \param mipmaps true to generate mipmaps
	 */
	Texture(const void* data, int colorComponents, size_t width, size_t height,
	        GLenum format, GLenum type, bool mipmaps = true);

	~Texture();

	//! Used by the material system to activate this texture
	void activateTexture();

	size_t getWidth() const { return width; }

	size_t getHeight() const { return height; }

	//! Gets the OpenGL ID of this texture
	unsigned int getID() { return id; }

	//! Gets the map of integer parameters set when the texture is activated
	std::map<GLenum, int> intParams;
	//! Gets the map of float parameters set when the texture is activated
	std::map<GLenum, float> floatParams;

private:
	void init(const void* data, int colorComponents,
	          size_t width, size_t height,
	          GLenum format, GLenum type, bool mipmaps);

	unsigned int id;
	size_t width;
	size_t height;
	bool hasMipmaps;
};
