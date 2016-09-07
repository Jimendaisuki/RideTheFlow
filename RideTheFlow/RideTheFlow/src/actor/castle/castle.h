#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>
#include "../../time/Time.h"
#include "../particle/BreakCastle.h"
#include "../../UIactor/EnemyHP.h"

struct CastleEnemyPos
{
	Vector3 cannon01;
	Vector3 cannon02;
	Vector3 cannon03;
	Vector3 cannon04;
	Vector3 varistor01;
	Vector3 varistor02;
	Vector3 varistor03;
	Vector3 varistor04;
	Vector3 Spear01;
	Vector3 Spear02;
	Vector3 Spear03;
	Vector3 Spear04;
	Vector3 Soldier01;
	Vector3 Soldier02;
	Vector3 Soldier03;
	Vector3 Soldier04;
	Vector3 Soldier05;
	Vector3 Soldier06;
	Vector3 Soldier07;
	Vector3 Soldier08;
};


class Castle : public Actor, public std::enable_shared_from_this<Castle>
{
public:
	Castle(IWorld& world, Vector3 position,Actor& _parent,int rank,float rotateY,float scale);
	~Castle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	Vector3 GetVelocity()
	{
		return velocity;
	}
	bool isLookPlayer()
	{
		return isLook;
	}
	bool GetDeadRagFlag()
	{
		return deadRagFlag;
	}
	void SetRank(int rank)
	{
		mRank = rank;
	}
private:
	void CastleEnemyPosSet();
private:
	Vector3 mPosition;
	Vector3 mScale;
	float mScaleFloat;
	float mRotateY;

	//無敵時間
	float damageCount;
	bool isDamage;
	//城の移動量
	Vector3 velocity;
	Vector3 sevePos;
	Vector3 prevPos;

	//城移動
	Vector3 startPos;
	Vector3 endPos;
	bool isLook;
	int mRank;
	int prevRank;
	float castleUpTimer;

	//死んだラグ
	float deadRagCount;
	bool deadRagFlag;
	bool deadMasterCastle;
	CastleEnemyPos castleEnemyPos;
	//死因
	BREAK_SELECT breakSelect;

	// HPバー
	EnemyHP		gauge;
};