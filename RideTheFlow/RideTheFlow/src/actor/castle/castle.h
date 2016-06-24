#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>
#include "../../time/Time.h"
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
	Castle(IWorld& world, Vector3 position,Actor& _parent,int rank,float rotateY);
	~Castle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	Vector3 GetVelocity()
	{
		return velocity*Time::DeltaTime;
	}
	bool isLookPlayer()
	{
		return isLook;
	}
private:
	void CastleEnemyPosSet();
private:
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 mScale;
	Actor* parent;
	Vector3 velocity;

	bool isLook;
	bool castleDown;
	int arrowCount;
	float attackRag;
	float mAttackTime;
	float mSecondAttack;
	float mArrowNumber;
	int mRank;
	float mRotateY;

	bool damage;
	float InvincibleTimer;
	CastleEnemyPos castleEnemyPos;

	Vector3 test;
};