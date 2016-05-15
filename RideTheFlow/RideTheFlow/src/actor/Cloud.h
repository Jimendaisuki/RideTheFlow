#pragma once
#include "Actor.h"
#include <vector>
#include <memory>

//�_
class Cloud :public Actor, public std::enable_shared_from_this<Cloud>
{
public:
	Cloud(IWorld& world, const Vector3& position_);
	~Cloud();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//�_�̈ʒu���΂�����邽�߂̔z��
	std::vector<Vector3> cloudPositions;
	//�T�C�Y
	std::vector<float> cloudsizes;


	//���݂̍��W
	Vector3 position;
	//�ړ�����
	Vector3 moveVec;
	//�ړ����x
	float moveSpeed;
	//�ړ������؂�ւ��p�^�C�}�[
	float moveChangeTimer;
	float moveChangeTime;

	//�Z���t�r���{�[�h�v�Z�p�A�J��������v�Z
	Vector3 up;
	Vector3 front;
	Vector3 left;
};