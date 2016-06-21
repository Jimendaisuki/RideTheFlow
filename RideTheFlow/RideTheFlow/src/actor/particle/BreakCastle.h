#pragma once
#include "../Actor.h"
#include <vector>
#include "../Player.h"
#include "ParticleSystem.h"

//������I��
enum CASTLE_SELECT
{
	MASTER_CASTLE,
	CHILD_CASTLE,
};

//������I��
enum BREAK_SELECT
{
	TORNADO,
	WIND,
	WIND_BALL,
};

class BreakCastle :public Actor, public ParticleSystem
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
	//��Ɖ������R���X�g���N�^�őI��
	CASTLE_SELECT castleSelect;
	BREAK_SELECT breakSelect;
	float rotX, rotY;
};