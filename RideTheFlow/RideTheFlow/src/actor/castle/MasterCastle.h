#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include<memory>

class MasterCastle : public Actor,public std::enable_shared_from_this<MasterCastle>
{
public:
	MasterCastle(IWorld& world, Vector3 position);
	~MasterCastle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Matrix4 playerMat;
	Vector3 mScale;
	Vector3 mPosition;
	Vector3 toPoint;
	float attackTime;
	float castleTime;
	float attackRag;
	int mRank;
	int arrowCount;
	float clor;
	bool isLook;
};