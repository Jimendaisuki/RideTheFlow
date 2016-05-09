#pragma once
#include "Actor.h"
#include "../math/Vector3.h"
#include <memory>

class Player :public Actor, public std::enable_shared_from_this<Player>
{
public:
	Player(IWorld& world);
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	void ParameterDraw()const;
	Vector3 position;
	float upAngle, leftAngle;
	float speedRegulation;
	float rotateUp, rotateLeft;
	std::vector<Vector3> posStorage;
	int boneSelect;
	Matrix4* rotateMat;
	int deletePosStorageCount;
	Vector3* vertexVec;

	Matrix4 cameraMat;

	float tornadeTimer;

	bool damageFlag;
	float damageCount;

	bool tackleFlag, tackleEndFlag,leftStickMove;
	Matrix4 tackleRotate;
	float tackleAngle;
	Vector3 tackleT;
	Vector3 nonPosStorageVec;

	Vector3 beforeVec;

	float animTime, totalTime;
	int modelHandle,animIndex;

	float animBlend;
	bool waitAnimSet;
};