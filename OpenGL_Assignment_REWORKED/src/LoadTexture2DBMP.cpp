#include "LoadTexture2DBMP.h"

LoadTexture2DBMP::LoadTexture2DBMP()
{
}

LoadTexture2DBMP::LoadTexture2DBMP(const char* path)
{
	Load(path);
}

LoadTexture2DBMP::~LoadTexture2DBMP()
{
}

GLuint LoadTexture2DBMP::Load(const char* path)
{
	std::ifstream inFile;
	inFile.open(path, std::ios::binary);
	if (!inFile.good()) {
		std::cerr << "Couldn't open bmp texture file " << path << std::endl;
	}
	inFile.seekg(0, std::ios::beg);

	// Read header of BMP and check whether file is actually BMP
	inFile.read((char*)&header, sizeof(bmpfile_header));
	if (header.file_type != 0x4D42) {
		std::cerr << "File is not an BMP!" << std::endl;
		return 0;
	}

	// Read bmp information off the file
	inFile.read((char*)&bitMapInfo, sizeof(BITMAPINFOHEADER));
	if (bitMapInfo.height != bitMapInfo.width) {
		std::cerr << "Texture is not square!" << std::endl;
		return 0;
	}

	// Read Colour Information
	std::unique_ptr<char[]>image_buffer(new char[bitMapInfo.bmp_bytesz]());
	inFile.seekg(header.offset_data, std::ios::beg);
	inFile.read(image_buffer.get(), bitMapInfo.bmp_bytesz);
	inFile.close();

	std::cout << path << " loaded." << std::endl;

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitMapInfo.width, bitMapInfo.height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image_buffer.get());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}