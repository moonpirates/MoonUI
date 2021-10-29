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
	
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	unsigned int GetID() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

private:
	unsigned int id;
	std::string path;
	unsigned char* localBuffer;
	int width;
	int height;
	int bitsPerPixel;
};

