#pragma once
#include "../Actor.h"
#include <vector>
#include <memory>
#include "ParticleSystem.h"
#include "../tornado/Tornado.h"

//������I��
enum CASTLE_SELECT
{
	MASTER_CASTLE,
	CHILD_CASTLE,
};

//������I��
enum BREAK_SELECT
{
	//����
	TORNADO,
	//����
	WIND_FLOW,
	//��C�C
	WIND_BALL,
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

	void CastleEmissive(const Vector3& vec_);
	Vector3 RandomVelocity();

private:
	Vector3 velocity;
	//��Ɖ������R���X�g���N�^�őI��
	CASTLE_SELECT castleSelect;
	BREAK_SELECT breakSelect;
};