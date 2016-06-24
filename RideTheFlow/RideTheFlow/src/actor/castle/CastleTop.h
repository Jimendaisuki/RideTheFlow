#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include "MasterCastle.h"
#include <memory>

class CastleTop : public Actor, public std::enable_shared_from_this<CastleTop >
{
public:
	CastleTop(IWorld& world, Vector3 position, MasterCastle& mc,float rotateY);
	~CastleTop();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	void CastleEnemyPosSet();
private:
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 velocity;
	MasterCastle* mMc;
	Vector3 sevePos;
	bool castleDown;

	bool noCol;
	float noColTimer;
	int mRank;

	float mRotateY;
};