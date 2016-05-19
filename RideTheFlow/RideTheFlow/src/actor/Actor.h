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
};

class Actor{
public:
	Actor(IWorld& world_);
	~Actor();
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	void Collide(COL_ID id, Actor& other);
	virtual bool IsDead() const{ return parameter.isDead; }
	ActorParameter GetParameter() const;

private:
	std::map<COL_ID, std::function<CollisionParameter(const Actor&)>> colFunc;

	CollisionParameter Player_vs_Stage(const Actor& other) const;


	/* ��vs */
	// ���ƒe
	CollisionParameter Player_vs_Bullet(const Actor& other) const;
	CollisionParameter Player_vs_Tornado(const Actor& other) const;

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

	/*  */
	CollisionParameter BoundarySphere_Capsule(const Actor& other)  const;

	// �_�ƕ��̓����蔻��(�� vs �J�v�Z���̏W��)
	CollisionParameter Cloud_vs_Wind(const Actor& other) const;

	//��ƃv���C���[�����񂾐��Ɖ_�̂����蔻��
	CollisionParameter PlayerCastleLine_vs_Cloud(const Actor& other) const;

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