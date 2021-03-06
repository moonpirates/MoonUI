#include "Texture.h"

Texture::Texture(const std::string path) :
	id(0), path(path), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0), slot(-1)
{
	stbi_set_flip_vertically_on_load(true);
	localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4); // RGBA = 4 channels

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	LOG("Created texture with ID: " << id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // How to act when scaling down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // How to act when scaling up
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // To to act when wrapping on sides
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // To to act when wrapping on top/bottom

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localBuffer)
	{
		stbi_image_free(localBuffer);
	}
}

Texture::~Texture()
{
	LOG("Texture destructor");
	Unbind();
	glDeleteTextures(1, &id);
}

void Texture::Bind(unsigned int slot)
{
	LOG("Binding texture at slot index " << slot << " on id " << id);
	this->slot = slot;
	//glActiveTexture(GL_TEXTURE0 + slot);
	//glBindTexture(GL_TEXTURE_2D, id);
	glBindTextureUnit(slot, id);
}

void Texture::Unbind() const
{
	LOG("Unbinding texture at slot index " << slot);
	// Deactivate? Unbinds all textures?
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::GetID() const
{
	return id;
}

unsigned int Texture::GetWidth() const
{
	return width;
}

unsigned int Texture::GetHeight() const
{
	return height;
}

const std::string& Texture::GetPath() const
{
	return path;
}

unsigned int Texture::GetSlot() const
{
	return slot;
}
