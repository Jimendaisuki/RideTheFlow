#include "Actor.h"
#include "Collision.h"
#include "../world/IWorld.h"

#include "../math/Math.h"
#include <list>


Actor::Actor(IWorld& world_) :world(world_)
{
	colFunc[COL_ID::SPHERE_SPHERE_COL] = std::bind(&Actor::SphereSphere, this, std::placeholders::_1);
	colFunc[COL_ID::CYLINDER_BOX_COL] = std::bind(&Actor::CylinderBox, this, std::placeholders::_1);
}

Actor::~Actor(){

}

void Actor::Collide(COL_ID id, Actor& other){
	CollisionParameter colpara = colFunc[id](other);
	if (colpara.colFlag)
	{
		OnCollide(other, colpara);
		other.OnCollide(*this, colpara);
	}
}

//���Ƌ��̂����蔻��
CollisionParameter Actor::SphereSphere(const Actor& other) const{
	CollisionParameter colpara;
	if (Vector3::Distance(Matrix4::GetPosition(parameter.mat), Matrix4::GetPosition(other.parameter.mat))
		< (parameter.radius + other.parameter.radius))colpara.colFlag = true;
	return colpara;
}

//
CollisionParameter Actor::CapsuleCapsule(const Actor& other) const{
	CollisionParameter colpara;

	/* TornadoData */
	Vector3 tBottomPos  = Matrix4::GetPosition(parameter.mat);
	Vector3 tTopPos		= tBottomPos + Matrix4::GetScale(parameter.mat).y;
	float	tRadius		= parameter.radius;

	/* otherData */
	Vector3 startPos, endPos, minPos, maxPos;
	Vector3 otherScale = Matrix4::GetScale(other.parameter.mat);
	minPos = Matrix4::GetPosition(other.parameter.mat) - otherScale * Vector3(1, 0, 1) / 2;
	maxPos = Matrix4::GetPosition(other.parameter.mat) - otherScale * Vector3(1, 2, 1) / 2;


	if (otherScale.y >= otherScale.x && otherScale.y >= otherScale.z)
	{
		auto max = otherScale.x;
		if (max >= otherScale.z){

		}
	}


	//if (HitCheck_Capsule_Capsule(tTopPos,  tBottomPos, tRadius))
	//{

	//}

	return colpara;
}



// �~���Ɣ��̓����蔻��
CollisionParameter Actor::CylinderBox(const Actor& other) const{
	CollisionParameter colpara;

	/* �~���f�[�^ */
	// �~���̎��ƒ�ʂ̌�������Q�_
	Vector3 TopPos		= Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	Vector3 BottomPos	= Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	// �Q�_�Ԃ̃x�N�g��
	float L = Vector3::Distance(TopPos, BottomPos);

	/* ���f�[�^ */
	// ���̑傫�����擾
	Vector3 BoxScale = Matrix4::GetScale(other.parameter.mat);
	// ��]�p���擾
	Vector3 rotate = Matrix4::GetRotate(other.parameter.mat);
	rotate = rotate * 180 / PI;
	
	// ���̕��������Z�o
 	Vector3 split;
	split.x = (int)(BoxScale.x / parameter.radius) + 1;
	split.z = (int)(BoxScale.z / parameter.radius) + 1;
	split.y = (int)(BoxScale.y / L) + 1;
	if (split.x <= 1) split.x = 2;
	if (split.y <= 1) split.y = 2;
	if (split.z <= 1) split.z = 2;

	// �ӂ̒�����ݒ�
	Vector3 side;
	side.x = BoxScale.x / split.x;
	side.y = BoxScale.y / split.y;
	side.z = BoxScale.z / split.z;

	// ��_
	//Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) / 2);						// �I�u�W�F�N�g�̒��S�iUnity�����j
	Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 1) / 2);	// ���f���̒�ʒ��S

	// ���̓_�̕ۑ�
	std::list<Vector3> points;
	for (int z = 0; z <= split.z; z++)
	{
		for (int y = 0; y <= split.y; y++)
		{
			for (int x = 0; x <= split.x; x++)
			{
				if ((x == 0 || x == split.x) || (y == 0 || y == split.y) || (z == 0 || z == split.z))
				{
					Vector3 point = p + Vector3(side.x * x, side.y * y, side.z * z);

					Vector3 aaa = point - Matrix4::GetPosition(other.parameter.mat);

					// ���W�ϊ�
					auto temp =
						Matrix4::Translate(-aaa) *
						Matrix4::RotateZ(rotate.z) *
						Matrix4::RotateX(rotate.x) *
						Matrix4::RotateY(rotate.y) *
						Matrix4::Translate(Matrix4::GetPosition(other.parameter.mat));

					points.push_back(Matrix4::GetPosition(temp));
				}
			}
		}
	}

	// ���_�Ɖ~���̓����蔻��
	for each (Vector3 p in points)
	{
		float S1 = Vector3::Distance(TopPos, p);
		float S2 = Vector3::Distance(BottomPos, p);

		float l = (S1 * S1 - L * L - S2 * S2) / (-2 * L);

		if (!(l < 0.0f || l > L))
		{
			// ���a�Ɛ������r
			auto qq = S2 * S2 - l * l;
			if (qq <= parameter.radius * parameter.radius)	colpara.colFlag = true;
		}
	}

	points.clear();
	return colpara;

	
}

ActorParameter Actor::GetParameter() const
{
	return parameter;
}