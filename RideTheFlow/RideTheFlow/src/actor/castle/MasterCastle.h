#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include "CastleParameter.h"
#include<memory>
#include "../particle/BreakCastle.h"

class MasterCastle : public Actor,public std::enable_shared_from_this<MasterCastle>
{
public:
	MasterCastle(IWorld& world, Vector3 position, float rotateY, bool spawnShip, bool title);
	MasterCastle(IWorld& world, Vector3 position, float rotateY, bool spawnShip, bool title, Actor* _parent);
	~MasterCastle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	bool castleRankUp()
	{
		return rankUp;
	}
	void castleLost()
	{
		testRnak--;
		parameter.height = Vector3(0.0f, 70.0f + 34.0f*testRnak, 0.0f);
	}
	int getRank()
	{
		return Rank - mRank;
	}
	void RankUp()
	{
		rankUp = true;
	}
	BREAK_SELECT getBreakSelect()
	{
		return breakSelect;
	}
	Vector3 getTornadoVelocity()
	{
		return tornadoVelocity;
	}

private:
	Matrix4 playerMat;
	Vector3 mScale;
	Vector3 mPosition;
	Vector3 toPoint;
	float mRotateY;


	//Ï‚İd‚È‚ééŠÖŒW
	bool rankUp;
	int mRank;

	int testRnak;
	//oŒ»‚·‚é“GŠÖŒW
	float spawanArmyTimer;
	float spawnShipTimer;
	bool mSpawnShip;

	float rankUpHeght;

	//–³“GŠÖŒW
	bool damage;
	float InvincibleTimer;

	//€ˆö
	BREAK_SELECT breakSelect;
	//—³Šª‚Å€‚ñ‚¾ê‡‚Ì—³Šª‚ÌˆÚ“®—Ê
	Vector3 tornadoVelocity;

	//ƒ^ƒCƒgƒ‹
	bool mTitle;
};