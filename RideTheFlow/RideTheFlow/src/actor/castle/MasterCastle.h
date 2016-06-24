#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include "CastleParameter.h"
#include<memory>

class MasterCastle : public Actor,public std::enable_shared_from_this<MasterCastle>
{
public:
	MasterCastle(IWorld& world, Vector3 position,bool spawnShip,bool title,float rotateY);
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

private:
	Matrix4 playerMat;
	Vector3 mScale;
	Vector3 mPosition;
	Vector3 toPoint;
	float mRotateY;

	//�U���֌W
	float mSecondAttack;
	float mArrowNumber;
	float attackTime;
	float attackRag;
	int arrowCount;

	//�ςݏd�Ȃ��֌W
	bool rankUp;
	bool rankUpRag;
	float rankUpRagTimer;
	float castleTime;
	int mRank;

	int testRnak;
	//�o������G�֌W
	float spawanArmyTimer;
	float spawnShipTimer;
	bool mSpawnShip;
	bool downCastle;


	//���G�֌W
	bool damage;
	float InvincibleTimer;

	//�^�C�g��
	bool mTitle;
};