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

//ãÖÇ∆ãÖÇÃÇ†ÇΩÇËîªíË
CollisionParameter Actor::SphereSphere(const Actor& other) const{
	CollisionParameter colpara;
	if (Vector3::Distance(Matrix4::GetPosition(parameter.mat), Matrix4::GetPosition(other.parameter.mat))
		< (parameter.radius + other.parameter.radius))colpara.colFlag = true;
	return colpara;
}

// â~íåÇ∆î†ÇÃìñÇΩÇËîªíË
CollisionParameter Actor::CylinderBox(const Actor& other) const{
	CollisionParameter colpara;

	/* â~íåÉfÅ[É^ */
	// â~íåÇÃé≤Ç∆íÍñ ÇÃåç∑Ç∑ÇÈÇQì_
	Vector3 TopPos		= Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	Vector3 BottomPos	= Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	// ÇQì_ä‘ÇÃÉxÉNÉgÉã
	float L = Vector3::Distance(TopPos, BottomPos);

	/* î†ÉfÅ[É^ */
	// î†ÇÃëÂÇ´Ç≥ÇéÊìæ
	Vector3 BoxScale = Matrix4::GetScale(other.parameter.mat);
	// âÒì]äpÇéÊìæ
	Vector3 rotate = Matrix4::GetRotate(other.parameter.mat);
	rotate = rotate * 180 / PI;
	
	// î†ÇÃï™äÑêîÇéZèoÅií∏ì_êîÇãÅÇﬂÇÈÇΩÇﬂåãâ Ç…Å{ÇPÇ∑ÇÈÅj
 	Vector3 split;
	split.x = (int)(BoxScale.x / parameter.radius) + 1;
	split.z = (int)(BoxScale.z / parameter.radius) + 1;
	split.y = (int)(BoxScale.y / L) + 1;

	// ï”ÇÃí∑Ç≥Çê›íË
	Vector3 side;
	side.x = BoxScale.x / split.x;
	side.y = BoxScale.y / split.y;
	side.z = BoxScale.z / split.z;

	// äÓèÄì_
	Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) / 2);

	// î†ÇÃì_ÇÃï€ë∂
	std::list<Vector3> points;
	for (int z = 0; z <= split.z; z++)
	{
		for (int y = 0; y <= split.y; y++)
		{
			for (int x = 0; x <= split.x; x++)
			{
				Vector3 point = p + Vector3(side.x * x, side.y * y, side.z * z);
				points.push_back(point);
			}
		}
	}
	// ç¿ïWïœä∑
	for each (Vector3 p in points)
	{
		auto temp =
			Matrix4::Translate(p) *
			Matrix4::RotateZ(rotate.z) *
			Matrix4::RotateX(rotate.x) *
			Matrix4::RotateY(rotate.y) *
			Matrix4::Translate(Matrix4::GetPosition(other.parameter.mat));

		p = Matrix4::GetPosition(temp);
	}

	// í∏ì_Ç∆â~íåÇÃìñÇΩÇËîªíË
	for each (Vector3 p in points)
	{
		float S1 = Vector3::Distance(TopPos, p);
		float S2 = Vector3::Distance(BottomPos, p);

		float l = (S1 * S1 - L * L - S2 * S2) / (-2 * L);

		if (!(l < 0.0f || l > L))
		{
			// îºåaÇ∆ê¸ï™Çî‰är
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