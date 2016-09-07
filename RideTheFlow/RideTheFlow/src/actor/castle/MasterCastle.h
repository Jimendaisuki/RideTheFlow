#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include "CastleParameter.h"
#include<memory>
#include "../particle/BreakCastle.h"
#include "../tornado/Tornado.h"
#include "../../UIactor/EnemyHP.h"
#include "castle.h"
#include <array>
#include <list>
class MasterCastle : public Actor,public std::enable_shared_from_this<MasterCastle>
{
public:
	MasterCastle(IWorld& world, Vector3 position,float scale, float rotateY, bool spawnShip, bool title,int titleRank);
	~MasterCastle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	void DamageWind(Vector3 position);
	void DamageAirGun(Vector3 position);
	void DamageTornad(Vector3 position);

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
		return castlesList.size();
	}
	void RankUp()
	{
		rankUp = true;
	}
	void SpawnEnemy()
	{
		spawnEnemyFlag = true;
	}
	bool SpawnDecision()
	{
		return mSpawnShip;
	}
	BREAK_SELECT getBreakSelect()
	{
		return breakSelect;
	}
	bool NoRankUp()
	{
		return noRankUp;
	}

private:
	Vector3 mScale;
	Vector3 mPosition;
	float mRotateY;
	float mScaleFloat;

	//€‚Êƒ‰ƒO
	bool isDeadRag;


	//Ï‚İd‚È‚ééŠÖŒW
	bool rankUp;
	int mRank;
	int testRnak;
	bool noRankUp;

	//oŒ»‚·‚é“GŠÖŒW
	bool mSpawnShip;
	bool spawnEnemyFlag;


	//–³“GŠÖŒW
	bool damage;
	float InvincibleTimer;

	//€ˆö
	BREAK_SELECT breakSelect;
	float deadRagTimer;

	//ƒ^ƒCƒgƒ‹
	bool mTitle;
	int mTitleRank;
	
	// HPƒo[
	EnemyHP		gauge;

	std::array<Castle*, 5> castles;

	std::list<Castle*> castlesList;

};