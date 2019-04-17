#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include <glew.h>

/// <summary> 24bit BMP Only, needs to be a square texture with dimensions to the power of 2 (64x64, 128x128, 256x256...)! </summary>
class LoadTexture2DBMP
{
private:
#pragma pack(push, 1) // Remove padding, so size is correct to 2 bytes
	struct bmpfile_header
	{
		uint16_t file_type{ 0x4D42 };
		uint32_t file_size{ 0 };
		uint16_t creator1{ 0 };
		uint16_t creator2{ 0 };
		uint32_t offset_data{ 0 };
	};

	struct BITMAPINFOHEADER
	{
		uint32_t headerSz{ 0 };
		int32_t width{ 0 };
		int32_t height{ 0 };
		uint16_t nplanes{ 1 };
		uint16_t bitspp{ 0 };
		uint32_t compress_type{ 0 };
		uint32_t bmp_bytesz{ 0 };
		int32_t hres{ 0 };
		int32_t vres{ 0 };
		uint32_t ncolours{ 0 };
		uint32_t nimpcolours{ 0 };
	};

	struct bmp_colour
	{
		unsigned char b, g, r;
	};
#pragma pack(pop)

private:
	bmpfile_header header;
	BITMAPINFOHEADER bitMapInfo;
	bmp_colour colour;

public:
	LoadTexture2DBMP();
	LoadTexture2DBMP(const char* path);
	~LoadTexture2DBMP();

	GLuint Load(const char* path);
};
