#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"

class MasterCastle : public Actor
{
public:
	MasterCastle(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale);
	~MasterCastle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	float attackTime;
	float castleTime;
	int mRank;
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 startPos;
	Vector3 endPos;
};