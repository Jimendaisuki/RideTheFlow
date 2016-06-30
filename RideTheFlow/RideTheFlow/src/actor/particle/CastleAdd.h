#pragma once
#include "../Actor.h"
#include <vector>
#include "../Player.h"
#include "ParticleSystem.h"

//�邪���z����Ƃ��ɂł�p�[�e�B�N��
class CastleAdd :public Actor, public ParticleSystem
{
public:
	//=======Actor======//
	//���[���h�A���W�A����������
	CastleAdd(IWorld& world, const Vector3& position_, int emissiveNum,float sizeBase_, float sizeAddMin_, float sizeAddMax_);
	~CastleAdd();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	float sizeBase, sizeAddMin, sizeAddMax;
};