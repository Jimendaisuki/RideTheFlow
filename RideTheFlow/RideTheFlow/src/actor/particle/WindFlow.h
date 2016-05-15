#pragma once
#include "../Actor.h"
#include <vector>
#include "../Player.h"
#include "ParticleSystem.h"

//�_�b�V�����ɐ������闬��
class WindFlow :public Actor,public ParticleSystem
{
public:
	//=======Actor======//
	WindFlow(IWorld& world, Player& player_);
	~WindFlow();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
	
	std::vector<Vector3>& GetDashPositions();

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	Player& player;
	//�v���C���[�Ƃ͕ʂɍ��W�z���ێ��i�_�b�V���I���܂Ŗ��t���[���擾�j
	std::vector<Vector3> dashPositions;
	//�_�b�V�����W�z��̎擾�������������H
	bool isSetting;
};