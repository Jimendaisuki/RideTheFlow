#pragma once
#include "ID.h"
#include <memory>
#include "../math/Vector3.h"

//�����蔻��̃p�����[�^
struct CollisionParameter{
	bool		colFlag	= false;				//���������ǂ����̃t���O		//�G����̍U���i㩁j���H
	Vector3		colPos	= Vector3::Zero;		// ���������|�W�V����
	int			colID;
};

// ����
struct Line{
	Vector3 startPos	= Vector3::Zero;	// �n�_
	Vector3 endPos		= Vector3::Zero;	// �I�_
};

// ��
struct Box{
	Vector3 min	= Vector3::Zero;			// ���̒��_
	Vector3 max = Vector3::Zero;			// ���̑Ίp�ɂ��钸�_
};

struct Sphere{
	Vector3	position	= Vector3::Zero;	// ���̈ʒu
	float	radius		= 0;				// ���̔��a
};

// �J�v�Z��
struct  Capsule{
	Vector3	startPos	= Vector3::Zero;	// �J�v�Z���̎n�_
	Vector3 endPos		= Vector3::Zero;	// �J�v�Z���̏I�_
	float	radius		= 0;				// ���a
};

// ���f��
struct ModelData{
	int		MHandle		= 0;
	int		MFrameIndex	= -1;
};

class Collisin{
public:
	// ���Ɣ��̓����蔻��
	static CollisionParameter SegmentBoxAABB(const Line& line, const Box& box);
	// ���Ƌ��̓����蔻��
	static CollisionParameter SegmentSphere(const Line& line, const Sphere& s);

	// ���Ƌ��̂����蔻��
	static CollisionParameter SphereSphere(const Sphere& s1, const Sphere& s2);
	// ���ƃJ�v�Z���̓����蔻��
	static CollisionParameter SphereCapsule(const Sphere& s, const Capsule& c);

	// �J�v�Z���ƃJ�v�Z���̓����蔻��
	static CollisionParameter CapsuleCapsule(const Capsule& c1, const Capsule& c2);
	// �J�v�Z���Ɠ_�̓����蔻��
	static CollisionParameter CapsulePoint(const Capsule& c, const Vector3& p);
	// �J�v�Z����AABB�̓����蔻��
	//CollisionParameter CapsuleAABBSegment(const Actor& other)const;

	// ���f���Ɛ����̓����蔻��
	static CollisionParameter ModelLine(const ModelData& model, const Line& line);
	// ���f���Ƌ��̓����蔻��
	static CollisionParameter ModelSphere(const ModelData& model, const Sphere& s);
	// ���f���ƃJ�v�Z���̓����蔻��
	static CollisionParameter ModelCapsule(const ModelData& model, const Capsule& c);

	// �~���Ɣ��̓����蔻��
	//CollisionParameter CylinderBox(const Actor& other)const;
};
