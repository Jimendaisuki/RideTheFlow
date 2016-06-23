#pragma once
#include "Actor.h"
#include "../math/Vector3.h"
#include <memory>
class WindFlow;
class Tornado;

struct TackleParameter{
	bool tackleFlag, tackleEndFlag,dashFlag,tackleColFlag,tornadoTatchFlag,airGunFlag;
	Matrix4 tackleRotate;
	float tackleAngle;
	Vector3 tackleT;
	float animTime;
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

	std::vector<Vector3>& ReturnBonePosStorage(){
		return bonePosStorage;
	}

	std::vector<Vector3>& ReturnDashPosStorage(){
		return dashPosStorage;
	}

	void Damage(float damage)
	{
		parameter.HP -= damage;
	}
	void ColSpear(Actor* parent);
	bool ReturnDead(){ return dead; }

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
	//�{�[���̈ʒu
	std::vector<Vector3> bonePosStorage;

	//�ړ���
	Vector3 vec;

	//�_���[�W���󂯂��ۂ̃p�����[�^�[
	bool damageFlag;
	float damageCount;
	bool dead;

	//�^�b�N���̃p�����[�^�[
	TackleParameter tp;

	//�����Q�[�W�̉񕜒�
	bool dashHealFlag;
	//�����p�̃X�s�[�h
	float dashSpeed;
	//�����ł��鎞��
	float dashTime;
	std::vector<Vector3> dashPosStorage;
	std::vector<int> tornadoPosStorage;
	std::shared_ptr<WindFlow> windFlowPtr;
	std::shared_ptr<Tornado> tornadoPtr;
	float tackleForTornadoTime;

	bool tornadoFlag;

	//posStorage�ɉ����Ȃ��Ƃ��̃{�[���̕���
	Vector3 nonPosStorageVec;

	//��]�̃f�B���C�������邽�߂ɗp����O�t���[���̃x�N�g��(y = 0.01f�̗��R�͂҂����肾�ƃo�O�𐶂��邩��)
	Vector3 beforeVec;

	//�A�j���[�V�����̍Đ��^�C��
	float totalTime;
	//���f���n���h�����擾����(�A�j���[�V�����̂��߂�)
	int modelHandle, animIndex;
	//�A�j���[�V�����̃u�����h
	float animBlend;
	//�ҋ@�A�j���[�V�������A�^�b�`�������ǂ������f
	bool waitAnimSet;

	bool moveFlag = true;
};