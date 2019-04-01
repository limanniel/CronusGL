#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "glew.h"

namespace ShaderLoader
{
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
}