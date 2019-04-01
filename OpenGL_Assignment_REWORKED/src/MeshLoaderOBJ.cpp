#include "MeshLoaderOBJ.h"


using namespace std;

namespace MeshLoaderOBJ 
{
	Mesh* Load(const char* path)
	{
		Mesh* mesh = new Mesh();
		////
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		ifstream inFile(path, ios::in);
		
		if (!inFile.good()) {
			cerr << "Cannot open" << path << endl;
		}

		string line;
		while (getline(inFile, line)) {
			// Load Vertex Data
			if (line.substr(0, 2) == "v ") {
				istringstream s(line.substr(2));
				glm::vec3 v;
				s >> v.x; s >> v.y; s >> v.z;
				temp_vertices.push_back(v);
			}

			// Load TexCoord's Data
			else if (line.substr(0, 3) == "vt ") {
				istringstream s(line.substr(3));
				glm::vec2 vt;
				s >> vt.x; s >> vt.y;
				temp_uvs.push_back(vt);
			}

			// Load Normal Data
			else if (line.substr(0, 3) == "vn ") {
				istringstream s(line.substr(3));
				glm::vec3 vn;
				s >> vn.x; s >> vn.y; s >> vn.z;
				temp_normals.push_back(vn);
			}
			
			// Load Face Data
			else if (line.substr(0, 2) == "f ") {
				GLushort vertexIndex[3], textureIndex[3], normalIndex[3];
				istringstream s(line.substr(2));
				for (int count = 0; count < 3; count++)
				{
					s >> vertexIndex[count];
					vertexIndices.push_back(vertexIndex[count]);
					s.ignore(numeric_limits<streamsize>::max(), '/');
					s >> textureIndex[count];
					uvIndices.push_back(textureIndex[count]);
					s.ignore(numeric_limits<streamsize>::max(), '/');
					s >> normalIndex[count];
					normalIndices.push_back(normalIndex[count]);
				}
			}
			// Ignore Comments
			else if (line[0] == '#') {
				
			}
			// Ignore anything else
			else {

			}
		}

		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];

			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			glm::vec3 normal = temp_normals[normalIndex - 1];

			//out_vertices.push_back(vertex);
			mesh->Vertices.push_back(vertex);
			//out_uvs.push_back(uv);
			mesh->UVCoords.push_back(uv);
			//out_normals.push_back(normal);
			mesh->Normals.push_back(normal);
		}
		
		std::cout << "OBJECT LOADED!" << std::endl;
		inFile.close();	
		return mesh;
	}
}
