#pragma once
#include "Actor.h"

//�X�e�[�W�ɂ�����t�H�O�𐧌�
class FogActor :public Actor
{
public:
	FogActor(IWorld& world);
	~FogActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
	float fogTotalPower;
	float angle;

	//�ǂ̊p�x����t�H�O�������邩
	float
};