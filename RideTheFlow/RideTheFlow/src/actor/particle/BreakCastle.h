#pragma once
#include "../Actor.h"
#include <vector>
#include <memory>
#include "ParticleSystem.h"
#include "../tornado/Tornado.h"
#include <functional>

//������I��
enum CASTLE_SELECT
{
	//��
	MASTER_CASTLE,
	CHILD_CASTLE,
	//��s�D
	SHIP,
	//����
	ISLE1,
	ISLE2,
	ISLE3,
	//�R��
	ARMY_ENEMY,
	//��
	HOME,
};

//������I��
enum BREAK_SELECT
{
	BREAK_BEGIN,
	//����
	TORNADO,
	//����
	WIND_FLOW,
	//��C�C
	WIND_BALL,
	DAMAGE,
	BREAK_END,
};

class BreakCastle :public Actor, public ParticleSystem, public std::enable_shared_from_this<BreakCastle>
{
public:
	//=======Actor======//
	BreakCastle(IWorld& world, const Vector3& position_, const CASTLE_SELECT& castle_, const BREAK_SELECT& break_);
	~BreakCastle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	//�����ɂ�����
	void TornadoBreakUpdate();
	void TornadoBreakEmissive();
	//����ɂ�����
	void WindFlowBreakUpdate();
	void WindFlowBreakEmissive();
	//��C�C�ɂ�����
	void WindBallBreakUpdate();
	void WindBallBreakEmissive();
	//�_���[�W�ɂ�����
	void DamageEmissive();

	void CastleWindFlowBreakEmissive( float scale_);
	void MasterCastleEmissive(const Vector3& vec_,float scale_);

	void ShipEmissive(std::function<Vector3()> vecFunc);
	void ArmyEnemyEmissive(std::function<Vector3()> vecFunc);

	void CastleDamageEmissive(std::function<Vector3()> vecFunc);
	void ShipDamageEmissive(std::function<Vector3()> vecFunc);

	void HomeEmissive();

	Vector3 RandomVelocity();

private:
	Vector3 velocity;
	//��Ɖ������R���X�g���N�^�őI��
	CASTLE_SELECT castleSelect;
	BREAK_SELECT breakSelect;

	//�����̓����ɂ��Ă���
	Tornado* pTornado;
};