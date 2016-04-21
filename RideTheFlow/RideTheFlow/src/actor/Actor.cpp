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

//球と球のあたり判定
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



// 円柱と箱の当たり判定
CollisionParameter Actor::CylinderBox(const Actor& other) const{
	CollisionParameter colpara;

	/* 円柱データ */
	// 円柱の軸と底面の交差する２点
	Vector3 TopPos		= Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	Vector3 BottomPos	= Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	// ２点間のベクトル
	float L = Vector3::Distance(TopPos, BottomPos);

	/* 箱データ */
	// 箱の大きさを取得
	Vector3 BoxScale = Matrix4::GetScale(other.parameter.mat);
	// 回転角を取得
	Vector3 rotate = Matrix4::GetRotate(other.parameter.mat);
	rotate = rotate * 180 / PI;
	
	// 箱の分割数を算出
 	Vector3 split;
	split.x = (int)(BoxScale.x / parameter.radius) + 1;
	split.z = (int)(BoxScale.z / parameter.radius) + 1;
	split.y = (int)(BoxScale.y / L) + 1;
	if (split.x <= 1) split.x = 2;
	if (split.y <= 1) split.y = 2;
	if (split.z <= 1) split.z = 2;

	// 辺の長さを設定
	Vector3 side;
	side.x = BoxScale.x / split.x;
	side.y = BoxScale.y / split.y;
	side.z = BoxScale.z / split.z;

	// 基準点
	//Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) / 2);						// オブジェクトの中心（Unity方式）
	Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 1) / 2);	// モデルの底面中心

	// 箱の点の保存
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

					// 座標変換
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

	// 頂点と円柱の当たり判定
	for each (Vector3 p in points)
	{
		float S1 = Vector3::Distance(TopPos, p);
		float S2 = Vector3::Distance(BottomPos, p);

		float l = (S1 * S1 - L * L - S2 * S2) / (-2 * L);

		if (!(l < 0.0f || l > L))
		{
			// 半径と線分を比較
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