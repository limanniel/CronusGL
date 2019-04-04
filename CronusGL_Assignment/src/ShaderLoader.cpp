#include "ShaderLoader.h"

namespace ShaderLoader 
{
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
	{
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read Vertex Shader Data
		std::string VertexShaderCode;
		std::ifstream v_InFile(vertex_file_path, std::ios::in);
		if (v_InFile.is_open()) {
			std::stringstream sstr;
			sstr << v_InFile.rdbuf();
			VertexShaderCode = sstr.str();
			v_InFile.close();
		}
		else {
			std::cerr << "Couldn't open " << vertex_file_path << " make sure that path is valid!" << std::endl;
			return 0;
		}

		// Read Fragment Shader Data
		std::string FragmentShaderCode;
		std::ifstream f_InFile(fragment_file_path, std::ios::in);
		if (f_InFile.is_open()) {
			std::stringstream sstr;
			sstr << f_InFile.rdbuf();
			FragmentShaderCode = sstr.str();
			f_InFile.close();
		}
		else {
			std::cerr << "Couldn't open " << fragment_file_path << " make sure that path is valid!" << std::endl;
			return 0;
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;
		// Compile Vertex Shader
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
		glCompileShader(VertexShaderID);
			// Check Vertex Shader
			glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
			glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0) {
				std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
				glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
				std::cerr << "Vertex Shader Compile Fail!: \n" << &VertexShaderErrorMessage[0] << std::endl;
			}

		// Compile Fragment Shader
		char const* FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
		glCompileShader(FragmentShaderID);
			// Check Fragment Shader
			glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
			glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0) {
				std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
				glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
				std::cerr << "Fragment Shader Compile Fail!: \n" << &FragmentShaderErrorMessage[0] << std::endl;
			}


		// Link Program
		std::cout << "Linking Program!" << std::endl;
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);
			// Check Program
			glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
			glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0) {
				std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
				glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
				std::cerr << "Program Compile Fail!: \n" << &ProgramErrorMessage[0] << std::endl;
			}

		// Clean Left-overs
		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		// Return Index to our program
		return ProgramID;
	}
}