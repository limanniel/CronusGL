#pragma once
#include "Structures.h"
#include "MeshLoaderOBJ.h"
#include "LoadTexture2DBMP.h"
#include "SceneNode_Static.h"

class Scene
{
private:
	LoadTexture2DBMP* _TextureManager;
	Model* _RoadStraight, *_Buildings;
	SceneNode_Static* _Straight1, * _Straight2, * _Straight3, * _Straight4;
	SceneNode_Static* _Buildings1, * _Buildings2, * _Buildings3, * _Buildings4;

public:
	Scene();
	~Scene();

	void Render();
	void Update();
};

