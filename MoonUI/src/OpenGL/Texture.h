#pragma once

#include <iostream>
#include <GL/glew.h>
#include <stb/stb_image.h>
#include <Macros/Macros.h>

class Texture
{
public:
	Texture(const std::string path);
	~Texture();
	
	void Bind(unsigned int slot);
	void Unbind() const;

	unsigned int GetID() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	const std::string& GetPath() const;
	unsigned int GetSlot() const;

private:
	unsigned int id;
	const std::string path;
	unsigned int slot;
	unsigned char* localBuffer;
	int width;
	int height;
	int bitsPerPixel;
};

