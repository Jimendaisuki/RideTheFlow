#pragma once
#include "../Actor.h"
#include <vector>
#include "../Player.h"
#include "ParticleSystem.h"

//�_�b�V�����̐�
class DashBlueLine :public Actor, public ParticleSystem
{
public:
	//=======Actor======//
	DashBlueLine(IWorld& world, Player& player_);
	~DashBlueLine();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
	void SetVec(Vector3 vec_) { vec = vec_; }
	//�_�b�V�����̋O�Ղ��擾
	std::vector<Vector3>& GetDashPositions();
	//�^�b�N���q�b�g��Ɉړ������������擾
	Vector3& GetMoveVec();

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	Player& player;
	//�v���C���[�Ƃ͕ʂɍ��W�z���ێ��i�_�b�V���I���܂Ŗ��t���[���擾�j
	std::vector<Vector3> dashPositions;
	//�_�b�V�����W�z��̎擾�������������H
	bool isSetting;
	//�^�b�N�����ꂽ��̈ړ�����
	Vector3 vec;
	//�^�b�N�����ꂽ��̈ړ����x
	float speed;
	//�����ʒu����̈ړ���
	Vector3 move;
	//�_�b�V���{�^�������͂���Ă��邩�H
	bool dashButtonState;
};