#include "Tank.h"



Tank::Tank()
	: W(false), S(false), A(false), D(false)
{
	_TextureManager = new LoadTexture2DBMP();

	_TankHullModel = new Model();
	_TankHullModel->Mesh = MeshLoaderOBJ::Load("res/models/TankHull.obj");
	_TankHullModel->Texture = _TextureManager->Load("res/textures/tankHull_diffuse.bmp");

	_TankTurretModel = new Model();
	_TankTurretModel->Mesh = MeshLoaderOBJ::Load("res/models/TankTurret.obj");
	_TankTurretModel->Texture = _TextureManager->Load("res/textures/tankTurret_diffuse.bmp");

	_TankTracksModel = new Model();
	_TankTracksModel->Mesh = MeshLoaderOBJ::Load("res/models/TankTracks.obj");
	_TankTracksModel->Texture = _TextureManager->Load("res/textures/tankTracks_diffuse.bmp");

	_TankHull = new SceneNode_Dynamic(_TankHullModel, glm::vec3(12.0f, 0.0f, 16.0f));
	_TankTurret = new SceneNode_Dynamic(_TankTurretModel);
	_TankTracks = new SceneNode_Dynamic(_TankTracksModel);

	_TankHull->AddChild(_TankTurret);
	_TankTurret->AddSibling(_TankTracks);
}


Tank::~Tank()
{
	delete _TextureManager;
	_TextureManager = nullptr;
	delete _TankHullModel;
	_TankHullModel = nullptr;
	delete _TankTurretModel;
	_TankTurretModel = nullptr;
	delete _TankTracksModel;
	_TankTracksModel = nullptr;
	delete _TankHull;
	_TankHull = nullptr;
	_TankTurret = nullptr;
	_TankTracks = nullptr;
}

void Tank::Render()
{
	_TankHull->Render();
}

void Tank::Update(float deltaTime)
{
	_turretRotateSesitivity = 0.010f * deltaTime;

	glm::mat4 tempMat = _TankHull->GetLocalTransform();
	if (W)
	{
		tempMat = glm::translate(tempMat, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	if (S)
	{
		tempMat = glm::translate(tempMat, glm::vec3(0.0f, 0.0f, -1.0f));
	}
	_TankHull->SetLocalTransform(tempMat);

	_TankHull->Update();
}

void Tank::MoveKeyDown(unsigned char key)
{
	if (key == 'w' || key == 'W')
	{
		W = true;
	}
	else if (key == 's' || key == 'S')
	{
		S = true;
	}
	else if (key == 'a' || key == 'A')
	{
		A = true;
	}
	else if (key == 'd' || key == 'D')
	{
		D = true;
	}
}

void Tank::MoveKeyUp(unsigned char key)
{
	if (key == 'w' || key == 'W')
	{
		W = false;
	}
	else if (key == 's' || key == 'S')
	{
		S = false;
	}
	else if (key == 'a' || key == 'A')
	{
		A = false;
	}
	else if (key == 'd' || key == 'D')
	{
		D = false;
	}
}

void Tank::RotateTurret(int x, int y)
{
	_turretYaw = _turretRotateSesitivity * float(800 / 2 - x);
	glm::mat4 tempMat = _TankTurret->GetLocalTransform();
	tempMat = glm::rotate(tempMat, glm::radians(_turretYaw), glm::vec3(0.0f, 1.0f, 0.0f));
	_TankTurret->SetLocalTransform(tempMat);
}
