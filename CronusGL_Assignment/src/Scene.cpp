#include "Scene.h"



Scene::Scene()
{
	_TextureManager = new LoadTexture2DBMP();
	_RoadStraight = new Model();
	_RoadStraight->Mesh = MeshLoaderOBJ::Load("res/models/roadStraight.obj");
	_RoadStraight->Texture = _TextureManager->Load("res/textures/Roadstraight.bmp");
	_Buildings = new Model();
	_Buildings->Mesh = MeshLoaderOBJ::Load("res/models/Buildings.obj");
	_Buildings->Texture = _TextureManager->Load("res/textures/building_diffuse.bmp");

	_Straight1 = new SceneNode_Static(_RoadStraight, glm::vec3(0.0f, 0.0f, 0.0f), Rotation(90, 0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	_Straight2 = new SceneNode_Static(_RoadStraight, glm::vec3(-108.0f, 0.0f, 0.0f), Rotation(), glm::vec3(1.0f, 1.0f, 1.0f));
	_Straight3 = new SceneNode_Static(_RoadStraight, glm::vec3(-108.0f, 0.0f, 0.0f), Rotation(), glm::vec3(1.0f, 1.0f, 1.0f));
	_Straight4 = new SceneNode_Static(_RoadStraight, glm::vec3(-108.0f, 0.0f, 0.0f), Rotation(), glm::vec3(1.0f, 1.0f, 1.0f));
	_Buildings1 = new SceneNode_Static(_Buildings, glm::vec3(-120.0f, 0.0f, 80.0f), Rotation(), glm::vec3(1.0f, 1.0f, 1.0f));
	_Buildings2 = new SceneNode_Static(_Buildings, glm::vec3(-120.0f, 0.0f, -80.0f), Rotation(), glm::vec3(1.0f, 1.0f, 1.0f));
	_Buildings3 = new SceneNode_Static(_Buildings, glm::vec3(-120.0f, 0.0f, 80.0f), Rotation(), glm::vec3(1.0f, 1.0f, 1.0f));
	_Buildings4 = new SceneNode_Static(_Buildings, glm::vec3(-120.0f, 0.0f, -80.0f), Rotation(), glm::vec3(1.0f, 1.0f, 1.0f));


	_Straight1->AddChild(_Straight2);
	_Straight1->AddChild(_Buildings1);
	_Buildings1->AddSibling(_Buildings2);

	_Straight2->AddChild(_Straight3);
	_Straight3->AddChild(_Straight4);
	_Straight3->AddChild(_Buildings3);
	_Buildings3->AddSibling(_Buildings4);
}


Scene::~Scene()
{
	delete _TextureManager;
	_TextureManager = nullptr;
	delete _RoadStraight;
	_RoadStraight = nullptr;
	delete _Straight1;
	_Straight1 = nullptr;
	_Straight2 = nullptr;
	_Straight3 = nullptr;
}

void Scene::Render()
{
	_Straight1->Render();
}

void Scene::Update()
{
	_Straight1->Update();
}
