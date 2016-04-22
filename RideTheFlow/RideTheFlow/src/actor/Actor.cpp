#include "Actor.h"
#include "Collision.h"
#include "../world/IWorld.h"

#include "../math/Math.h"
#include <list>


Actor::Actor(IWorld& world_) :world(world_)
{
	colFunc[COL_ID::SPHERE_SPHERE_COL] = std::bind(&Actor::SphereSphere, this, std::placeholders::_1);
	colFunc[COL_ID::CAPSULE_CAPSULE_COL] = std::bind(&Actor::CapsuleCapsule, this, std::placeholders::_1);
	colFunc[COL_ID::CAPSULE_AABB_COL] = std::bind(&Actor::CapsuleAABBSegment, this, std::placeholders::_1);
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

// カプセルとカプセルの当たり判定
CollisionParameter Actor::CapsuleCapsule(const Actor& other) const{
	CollisionParameter colpara;
	Capsule c1, c2;

	/* thisData */
	c1.startPos = Matrix4::GetPosition(parameter.mat);
	c1.endPos = c1.startPos + Matrix4::GetScale(parameter.mat) * Vector3::Up;
	c1.radius = parameter.radius;

	/* otherData */
	c2.startPos = Matrix4::GetPosition(other.parameter.mat);
	c2.endPos = c2.startPos + Matrix4::GetScale(other.parameter.mat)  * Vector3::Up;
	c2.radius = other.parameter.radius;

	if (HitCheck_Capsule_Capsule(
		c1.startPos, c1.endPos, c1.radius,
		c2.startPos, c2.endPos, c2.radius)) colpara.colFlag = true;

	return colpara;
}

// カプセルとAABBの当たり判定	（カプセルの半径より辺の間隔が長い場合は無効）
CollisionParameter Actor::CapsuleAABBSegment(const Actor& other)const
{
	CollisionParameter colpara;

	/* CapsuleData */
	Capsule c;
	c.startPos	= Matrix4::GetPosition(parameter.mat);
	c.endPos	= c.startPos + Matrix4::GetScale(parameter.mat) * Vector3::Up;
	c.radius	= parameter.radius;

	/* BoxData*/
	Vector3 min, max;
	min = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 1)) / 2;
	max = Matrix4::GetPosition(other.parameter.mat) + (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 2, 1)) / 2;
	Vector3 sideData[4];
	sideData[0] = Vector3::Zero;
	sideData[1] = Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 0);
	sideData[2] = Matrix4::GetScale(other.parameter.mat) * Vector3(0, 1, 0);
	sideData[3] = Matrix4::GetScale(other.parameter.mat) * Vector3(0, 0, 1);

	Vector3 v, v2;
	float length;
	for (int i = 1; i <= 3; i++)
	{
		v = max - sideData[i];

		length =
			Segment_Segment_MinLength(
			c.startPos, c.endPos,
			max, v);

		if (length <= parameter.radius)
		{
			colpara.colFlag = true;
			break;
		}
	}

	if (!colpara.colFlag)
	{
		for (int i = 0; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				if (colpara.colFlag) break;

				if (i != j)
				{
					v = min + sideData[i];
					v2 = v + sideData[j];
					length =
						Segment_Segment_MinLength(
						c.startPos, c.endPos,
						v, v2);

					if (length <= parameter.radius)	
						colpara.colFlag = true;
				}
			}
		}
	}

	return colpara;
}

//
CollisionParameter Actor::ModelLine(const Actor& other) const{
	CollisionParameter colpara;
	MV1_COLL_RESULT_POLY HitPoly;

	/* 線分データ */
	Vector3 startPos, endPos;
	startPos	= Matrix4::GetPosition(parameter.mat) - Vector3::Up * 300;
	endPos		= startPos + Matrix4::GetScale(parameter.mat) * Vector3::Up;

	//HitPoly = MV1CollCheck_Line(other.)
	if (HitPoly.HitFlag) colpara.colPos = HitPoly.HitPosition;

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