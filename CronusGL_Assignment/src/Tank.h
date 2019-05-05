#pragma once
#include "Structures.h"
#include "MeshLoaderOBJ.h"
#include "LoadTexture2DBMP.h"
#include "SceneNode_Dynamic.h"

class Tank
{
private:
	LoadTexture2DBMP* _TextureManager;
	Model* _TankHullModel, * _TankTurretModel, * _TankTracksModel;
	SceneNode_Dynamic* _TankHull, * _TankTurret, * _TankTracks;

	bool W, S, A, D;

public:
	Tank();
	~Tank();

	void Render();
	void Update(float deltaTime);
	void MoveKeyDown(unsigned char key);
	void MoveKeyUp(unsigned char key);
};

