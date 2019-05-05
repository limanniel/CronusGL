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
	float _turretYaw{ 0.0f };
	float _turretRotateSesitivity{ 0.0f };

public:
	Tank();
	~Tank();

	void Render();
	void Update(float deltaTime);
	void MoveKeyDown(unsigned char key);
	void MoveKeyUp(unsigned char key);

	inline const glm::mat4 GetTankModelMatrix() const { return _TankHull->GetLocalTransform(); }
	void RotateTurret(int x, int y);
};

