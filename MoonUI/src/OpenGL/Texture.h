#pragma once

#include <iostream>
#include <GL/glew.h>
#include "../Vendor/stb/stb_image.h"

class Texture
{
public:
	Texture(const std::string path);
	~Texture();
	
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

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

