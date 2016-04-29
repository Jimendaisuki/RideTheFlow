#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"

class MasterCastle : public Actor
{
public:
	MasterCastle(IWorld& world, Vector3 position);
	~MasterCastle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	float attackTime;
	float castleTime;
	float attackRag;
	int mRank;
	int arrowCount;
	Matrix4 playerMat;
	Vector3 mScale;
	Vector3 mPosition;
};