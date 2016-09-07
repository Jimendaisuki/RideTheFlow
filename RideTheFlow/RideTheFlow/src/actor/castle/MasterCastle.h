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

	//���ʃ��O
	bool isDeadRag;


	//�ςݏd�Ȃ��֌W
	bool rankUp;
	int mRank;
	int testRnak;
	bool noRankUp;

	//�o������G�֌W
	bool mSpawnShip;
	bool spawnEnemyFlag;


	//���G�֌W
	bool damage;
	float InvincibleTimer;

	//����
	BREAK_SELECT breakSelect;
	float deadRagTimer;

	//�^�C�g��
	bool mTitle;
	int mTitleRank;
	
	// HP�o�[
	EnemyHP		gauge;

	std::array<Castle*, 5> castles;

	std::list<Castle*> castlesList;

};