#include "MeshLoaderOBJ.h"


using namespace std;

struct PackedVertex;
void indexVBO(Mesh* Mesh);
bool getSimilarVertexIndex(PackedVertex& packed, std::map<PackedVertex, unsigned short>& VertexToOutIndex, unsigned short& result);

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

			mesh->Vertices.push_back(vertex);
			mesh->UVCoords.push_back(uv);
			mesh->Normals.push_back(normal);
		}
		
		std::cout << "OBJECT LOADED!" << std::endl;
		inFile.close();	

		indexVBO(mesh);

		return mesh;
	}
}

struct PackedVertex
{
	glm::vec3 vertex;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const { return memcmp((void*)this, (void*)& that, sizeof(PackedVertex)) > 0; };
};

bool getSimilarVertexIndex(PackedVertex& packed, std::map<PackedVertex,unsigned short>& VertexToOutIndex, unsigned short& result)
{
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}

void indexVBO(Mesh* Mesh)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	for (unsigned int i = 0; i < Mesh->Vertices.size(); i++)
	{
		PackedVertex packed = { Mesh->Vertices[i], Mesh->UVCoords[i], Mesh->Normals[i] };

		// Try to find similar vertex
		unsigned short index;
		bool found = getSimilarVertexIndex(packed, VertexToOutIndex, index);

		// Similar Vertex already in VBO
		if (found) {
			Mesh->Indices.push_back(index);
		}
		// Vertex not found/unique
		else {
			Mesh->indexed_Vertices.push_back(Mesh->Vertices[i]);
			Mesh->indexed_UVCoords.push_back(Mesh->UVCoords[i]);
			Mesh->indexed_Normals.push_back(Mesh->Normals[i]);
			unsigned short newIndex = (unsigned short)Mesh->indexed_Vertices.size() - 1;
			Mesh->Indices.push_back(newIndex);
			VertexToOutIndex[packed] = newIndex;
		}
	}
}