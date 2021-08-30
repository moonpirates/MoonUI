#pragma once

struct VertexBufferLayoutElement 
{
	unsigned int Type;
	unsigned int Count;
	unsigned char Normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 1;
		case GL_UNSIGNED_BYTE:
			return 1;
		}

		static_assert("Unknown type for GetSizeOfType()");

		return 0;
	}
};