#pragma once
#include "../AllInclude.h"
#include "ID.h"
#include "../graphic/Sprite.h"
#include <map>
#include <functional>
#include "../math/Matrix4.h"

class IWorld;
struct CollisionParameter;

struct ActorParameter
{
	ACTOR_ID id;
	bool isDead;
	float radius;
	Vector3 height;
	Matrix4 mat;
	float   HP;
	Vector3 velocity;
};

class Actor{
public:
	Actor(IWorld& world_);
	~Actor();
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	void Collide(COL_ID id, Actor& other);
	virtual bool IsDead() const{ return parameter.isDead; }
	void SetIsDead(bool flag){ parameter.isDead = flag; }
	ActorParameter GetParameter() const;

private:
	std::map<COL_ID, std::function<CollisionParameter(const Actor&)>> colFunc;

	CollisionParameter Player_vs_Stage(const Actor& other) const;


	/* ��vs */
	// ���ƒe
	CollisionParameter Player_vs_Bullet(const Actor& other) const;
	CollisionParameter Player_vs_Tornado(const Actor& other) const;
	CollisionParameter Player_vs_Wind(const Actor& other) const;
	//���ƑD�̓G
	CollisionParameter Player_vs_ShipEnemy(const Actor& other) const;
	//���ƌ�����
	CollisionParameter Player_vs_DoragonSpear(const Actor& other) const;
	CollisionParameter Player_vs_DoragonSpearWithin(const Actor& other)const;

	CollisionParameter Player_vs_Castle(const Actor& other)const;
	/* ����vs */
	// �����ƒe
	// �����Ɨ���


	/* ����vs */
	// �����ƃX�e�[�W�̓����蔻��
	CollisionParameter Tornado_vs_Stage(const Actor& other) const;
	// �����Ə�̓����蔻��
	CollisionParameter Tornado_vs_Castle(const Actor& other) const;
	// �����ƕ����̓����蔻��
	CollisionParameter Tornado_vs_IsLand(const Actor& other) const;
	// �����ƕ����̓����蔻��

	//�����ƓG�̂����蔻��
	CollisionParameter Tornado_vs_Enemy(const Actor& other) const;

	/*  */
	CollisionParameter BoundarySphere_Capsule(const Actor& other)  const;

	// �_�Ɨ����̓����蔻��
	CollisionParameter Cloud_vs_Tornado(const Actor& other) const;
	// �_�ƕ��̓����蔻��(�� vs �J�v�Z���̏W��)
	CollisionParameter Cloud_vs_Wind(const Actor& other) const;

	//��ƃv���C���[�����񂾐��Ɖ_�̂����蔻��
	CollisionParameter PlayerCastleLine_vs_Cloud(const Actor& other) const;
	//�R���ƃX�e�[�W�̂����蔻��
	CollisionParameter ArmyEnemy_vs_Stage(const Actor& other)const;
	// �e�ƕ��̓����蔻��(�� vs �J�v�Z���̏W��)
	CollisionParameter Bullet_vs_Wind(const Actor& other) const;

	//��̏�Ɖ��̏�̂����蔻�� 
	CollisionParameter Castle_vs_Castle(const Actor& other) const;
	//master��Ə�̂����蔻��
	CollisionParameter MasterCastle_vs_Castle(const Actor& other) const;
	//�D�ƕ����̂����蔻��
	CollisionParameter Ship_vs_Island(const Actor& other) const;
	//���ƓG�̂����蔻��
	CollisionParameter Enemy_vs_Wind(const Actor& other) const;
	//���Ə�̂����蔻��
	CollisionParameter Castle_vs_Wind(const Actor& other) const;

	//�D�ƑD�̂����蔻��
	CollisionParameter Ship_vs_Ship(const Actor& other)const;
	/* ��ō폜
	// ���Ɣ��̓����蔻��
	CollisionParameter SegmentBoxAABB(const Actor& other)const;
	// ���Ƌ��̓����蔻��
	CollisionParameter SegmentSphere(const Actor& other)const;
	// ���Ƌ��̂����蔻��
	CollisionParameter SphereSphere(const Actor& other)const;
	// ���ƃJ�v�Z���̓����蔻��
	CollisionParameter SphereCapsule(const Actor& other)const;
	// �J�v�Z���ƃJ�v�Z���̓����蔻��
	CollisionParameter CapsuleCapsule(const Actor& other)const;
	// �J�v�Z���Ɠ_�̓����蔻��
	CollisionParameter CapsulePoint(const Actor& other)const;
	// �J�v�Z����AABB�̓����蔻��
	CollisionParameter CapsuleAABBSegment(const Actor& other)const;
	// ���f���Ɛ����̓����蔻��
	CollisionParameter ModelLine(const Actor& other)const;
	// ���f���Ƌ��̓����蔻��
	CollisionParameter ModelSphere(const Actor& other)const;
	// ���f���ƃJ�v�Z���̓����蔻��
	CollisionParameter ModelCapsule(const Actor& other)const;
	// �~���Ɣ��̓����蔻��
	CollisionParameter CylinderBox(const Actor& other)const;
	*/


protected:
	virtual void OnCollide(Actor& other, CollisionParameter colpara) = 0;
	ActorParameter parameter;
	IWorld& world;

public:
	Actor* parent;
};