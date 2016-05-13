#pragma once
#include "Actor.h"
#include "../math/Vector3.h"
#include <memory>

struct TackleParameter{
	bool tackleFlag, tackleEndFlag,tackleAttackFlag,dashFlag;
	Matrix4 tackleRotate;
	float tackleAngle;
	Vector3 tackleT;
};

class Player :public Actor, public std::enable_shared_from_this<Player>
{
public:
	Player(IWorld& world);
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
	TackleParameter& ReturnTackleParameter(){
		return tp;
	}


private:
	//�f�o�b�N�\���܂Ƃ�
	void ParameterDraw()const;
	//�f�o�b�N�R�[�h(�f�o�b�N�\������Ă�����̂̃{�[���̃i���o�[)
	int boneSelect;

	//�v�Z�p�̃|�W�V����
	Vector3 position;
	//���˂��˂�����ׂ�angle�Q��
	float upAngle, leftAngle;
	//�J�����̏㉺���E��rotate
	float rotateUp, rotateLeft;
	//�}�C�t���[��position��ۑ��������
	std::vector<Vector3> posStorage;
	//�����{�[��
	Vector3* vertexVec;

	//�ړ���
	Vector3 vec;

	//�g���l�[�h����������܂ł̎���
	float tornadeTimer;

	//�_���[�W���󂯂��ۂ̃p�����[�^�[
	bool damageFlag;
	float damageCount;

	//�^�b�N���̃p�����[�^�[
	TackleParameter tp;

	//�����Q�[�W�̉񕜒�
	bool dashHealFlag;
	//�����p�̃X�s�[�h
	float dashSpeed;
	//�����ł��鎞��
	float dashTime;
	std::vector<Vector3> dashPosStorage;

	//posStorage�ɉ����Ȃ��Ƃ��̃{�[���̕���
	Vector3 nonPosStorageVec;

	//��]�̃f�B���C�������邽�߂ɗp����O�t���[���̃x�N�g��(y = 0.01f�̗��R�͂҂����肾�ƃo�O�𐶂��邩��)
	Vector3 beforeVec;

	//�A�j���[�V�����̍Đ��^�C��
	float animTime, totalTime;
	//���f���n���h�����擾����(�A�j���[�V�����̂��߂�)
	int modelHandle, animIndex;
	//�A�j���[�V�����̃u�����h
	float animBlend;
	//�ҋ@�A�j���[�V�������A�^�b�`�������ǂ������f
	bool waitAnimSet;
};