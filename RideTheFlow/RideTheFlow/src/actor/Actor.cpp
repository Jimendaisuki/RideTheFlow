#include "Actor.h"
#include "Collision.h"
#include "../world/IWorld.h"

#include "../math/Math.h"
#include <list>
#include <vector>

#include "../graphic/Model.h"
#include "Player.h"
#include "particle/WindFlow.h"
#include "Cloud.h"


Actor::Actor(IWorld& world_) :world(world_)
{
	colFunc[COL_ID::SPHERE_SPHERE_COL] = std::bind(&Actor::Player_vs_Bullet, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_STAGE_COL] = std::bind(&Actor::Player_vs_Stage, this, std::placeholders::_1);
	colFunc[COL_ID::TORNADO_STAGE_COL ] = std::bind(&Actor::Tornado_vs_Stage,  this, std::placeholders::_1);
	colFunc[COL_ID::TORNADO_CASTLE_COL] = std::bind(&Actor::Tornado_vs_Castle, this, std::placeholders::_1);
	colFunc[COL_ID::TORNADO_ISLAND_COL] = std::bind(&Actor::Tornado_vs_IsLand, this, std::placeholders::_1);

	colFunc[COL_ID::SPHERE_CAPSULE] = std::bind(&Actor::BoundarySphere_Capsule, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_TORNADO_COL] = std::bind(&Actor::Player_vs_Tornado, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_WIND_COL] = std::bind(&Actor::Player_vs_Wind, this, std::placeholders::_1);
	colFunc[COL_ID::CLOUD_WIND_COL] = std::bind(&Actor::Cloud_vs_Wind, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYERTOCASTLELINE_CLOUD_COL] = std::bind(&Actor::PlayerCastleLine_vs_Cloud, this, std::placeholders::_1);
	colFunc[COL_ID::CLOUD_TORNADO_COL] = std::bind(&Actor::Cloud_vs_Tornado, this, std::placeholders::_1);

	//colFunc[COL_ID::SPHERE_SPHERE_COL] = std::bind(&Actor::SphereSphere, this, std::placeholders::_1);
	//colFunc[COL_ID::CAPSULE_CAPSULE_COL] = std::bind(&Actor::CapsuleCapsule, this, std::placeholders::_1);
	//colFunc[COL_ID::CAPSULE_AABB_COL] = std::bind(&Actor::CapsuleAABBSegment, this, std::placeholders::_1);
	//colFunc[COL_ID::CYLINDER_BOX_COL] = std::bind(&Actor::CylinderBox, this, std::placeholders::_1);
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

CollisionParameter Actor::Player_vs_Stage(const Actor& other) const{
	CollisionParameter colpara;

	Sphere sphere;
	sphere.position = parameter.mat.GetPosition();
	sphere.radius = parameter.radius;

	/* ModelData */
	ModelData stage;
	stage.MHandle = Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL);
	stage.MFrameIndex = -1;

	bool flag = false;

	colpara = Collisin::GetInstace().ModelSphere(stage, sphere);

	/* ResultData */
	while (colpara.colFlag){
		sphere.position += colpara.colPos.Normalized() * 1.0f;
		flag = true;
		colpara = Collisin::GetInstace().ModelSphere(stage, sphere);
	}
	colpara.colPos = sphere.position;
	colpara.colFlag = flag;
	colpara.colID = COL_ID::PLAYER_STAGE_COL;

	return colpara;
}

/* 龍vs */
// 龍と弾の当たり判定
CollisionParameter Actor::Player_vs_Bullet(const Actor& other) const{
	CollisionParameter colpara;

	/* BulletData */
	Sphere bullet;
	bullet.position = Matrix4::GetPosition(other.parameter.mat);
	bullet.radius = other.parameter.radius;

	for (auto i : static_cast<Player*>(const_cast<Actor*>(this))->ReturnBonePosStorage()){
		/* PlayerData */
		Sphere player;
		player.position = i;
		player.radius = parameter.radius;
		/* ResultData */
		colpara = Collisin::GetInstace().SphereSphere(player, bullet);
		if (colpara.colFlag){
			break;
		}
	}
	colpara.colID = COL_ID::SPHERE_SPHERE_COL;

	return colpara;
}


CollisionParameter Actor::Player_vs_Tornado(const Actor& other) const{
	CollisionParameter colpara;
	if (HitCheck_Capsule_Capsule(parameter.mat.GetPosition(), parameter.mat.GetPosition() + parameter.height, parameter.radius,
		other.parameter.mat.GetPosition(), other.parameter.mat.GetPosition() + other.parameter.height, other.parameter.radius)){
		colpara.colFlag = true;
		colpara.colVelosity = parameter.height.Normalized();
		colpara.colID = COL_ID::PLAYER_TORNADO_COL;
	}
	return colpara;
}

CollisionParameter Actor::Player_vs_Wind(const Actor& other) const{
	//CollisionParameter colpara;
	//if (HitCheck_Capsule_Capsule(parameter.mat.GetPosition(), parameter.mat.GetPosition() + parameter.height, parameter.radius,
	//	other.parameter.mat.GetPosition(), other.parameter.mat.GetPosition() + other.parameter.height, other.parameter.radius)){
	//	colpara.colFlag = true;
	//	colpara.colVelosity = parameter.height.Normalized();
	//	colpara.colID = COL_ID::PLAYER_TORNADO_COL;
	//}
	CollisionParameter colpara;

	Capsule player;
	player.startPos = parameter.mat.GetPosition();
	player.endPos = parameter.mat.GetPosition() + parameter.height;
	player.radius = parameter.radius;

	WindFlow* w = static_cast<WindFlow*>(const_cast<Actor*>(&other));
	std::vector<Vector3> dashPositions = w->GetDashPositions();
	int dashPositionSize = dashPositions.size();
	if (dashPositionSize < 2)
	{		
		colpara.colID = COL_ID::PLAYER_WIND_COL;
		return colpara;
	}

	Capsule wind;
	wind.radius = other.parameter.radius;
	for (int i = 0; i < dashPositionSize; i++)
	{
		wind.startPos = dashPositions.at(i);
		wind.endPos = wind.startPos;
		wind.endPos.y = other.parameter.height.y;
		colpara = Collisin::GetInstace().CapsuleCapsule(player, wind);

		if (colpara.colFlag)
		{
			colpara.colID = COL_ID::PLAYER_WIND_COL;
			colpara.colVelosity = Vector3(parameter.height.x, 0.0f, parameter.height.z).Normalized();
			return colpara;
		}
	}
	colpara.colID = COL_ID::PLAYER_WIND_COL;
	return colpara;
}

/* 竜巻vs */
// 竜巻とステージの当たり判定
CollisionParameter Actor::Tornado_vs_Stage(const Actor& other) const{
	CollisionParameter colpara;

	/* TornadoData */
	Line tornado;
	tornado.startPos = Matrix4::GetPosition(parameter.mat);// -Vector3::Up * parameter.radius;
	tornado.endPos = Matrix4::GetPosition(parameter.mat) + parameter.height;

	/* ModelData */
	ModelData stage;
	stage.MHandle = Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL);
	stage.MFrameIndex = -1;

	/* ResultData */
	colpara = Collisin::GetInstace().ModelLine(stage, tornado);
	colpara.colID = COL_ID::TORNADO_STAGE_COL;

	return colpara;
}
// 竜巻と城の当たり判定
CollisionParameter Actor::Tornado_vs_Castle(const Actor& other) const{
	CollisionParameter colpara;

	/* TornadoData */
	Capsule tornado;
	tornado.startPos = Matrix4::GetPosition(parameter.mat);
	tornado.endPos = tornado.startPos + parameter.height;
	tornado.radius   = parameter.radius;

	/* CastleData */
	Capsule castle;
	castle.startPos = Matrix4::GetPosition(other.parameter.mat);
	castle.endPos = castle.startPos + other.parameter.height;
	castle.radius	= other.parameter.radius;

	/* ResultData */
	colpara = Collisin::GetInstace().CapsuleCapsule(tornado, castle);
	colpara.colID = COL_ID::TORNADO_CASTLE_COL;

	return colpara;
}
// 竜巻と浮島の当たり判定
CollisionParameter Actor::Tornado_vs_IsLand(const Actor& other) const{
	CollisionParameter colpara;

	/* TornadoData */
	Capsule tornado;
	tornado.startPos = Matrix4::GetPosition(parameter.mat);
	tornado.endPos = tornado.startPos + parameter.height;
	tornado.radius = parameter.radius;

	/* IslandData */
	Sphere island;
	island.position = Matrix4::GetPosition(other.parameter.mat);
	island.radius	= other.parameter.radius;

	colpara = Collisin::GetInstace().SphereCapsule(island, tornado);

	Capsule land;
	land.startPos = Matrix4::GetPosition(other.parameter.mat);
	land.endPos = Matrix4::GetPosition(other.parameter.mat) + Vector3::Up;
	land.radius = other.parameter.radius;

	colpara.colID = COL_ID::TORNADO_ISLAND_COL;
	return colpara;
}


CollisionParameter Actor::Cloud_vs_Tornado(const Actor& other) const{
	CollisionParameter colpara;

	Sphere cloud;
	cloud.position = Matrix4::GetPosition(parameter.mat);
	cloud.radius = parameter.radius;

	Capsule tornado;
	tornado.startPos = Matrix4::GetPosition(other.parameter.mat);
	tornado.endPos = tornado.startPos + other.parameter.height;
	tornado.radius = other.parameter.radius;

	colpara = Collisin::GetInstace().SphereCapsule(cloud, tornado);

	colpara.colID = COL_ID::CLOUD_TORNADO_COL;
	return colpara;
}
CollisionParameter Actor::Cloud_vs_Wind(const Actor& other) const{
	CollisionParameter colpara;

	Sphere cloud;
	cloud.position = Matrix4::GetPosition(parameter.mat);
	cloud.radius = parameter.radius;

	WindFlow* w = static_cast<WindFlow*>(const_cast<Actor*>(&other));
	std::vector<Vector3> dashPositions = w->GetDashPositions();
	int dashPositionSize = dashPositions.size();
	Vector3 move = w->GetMoveVec();

	if (dashPositionSize < 2)
	{
		colpara.colID = COL_ID::CLOUD_WIND_COL;
		return colpara;
	}

	Capsule wind;
	wind.radius = other.parameter.radius;
	for (int i = 0; i < dashPositionSize; i++)
	{
		wind.startPos = dashPositions.at(i) + move;
		wind.endPos = wind.startPos;
		wind.endPos.y = other.parameter.height.y;
		colpara = Collisin::GetInstace().SphereCapsule(cloud, wind);

		if (colpara.colFlag)
		{
			if (i == dashPositionSize - 1)
				colpara.colVelosity = Vector3::Normalize(dashPositions.at(i) - dashPositions.at(i - 1));
			else
				colpara.colVelosity = Vector3::Normalize(dashPositions.at(i + 1) - dashPositions.at(i));

			colpara.colID = COL_ID::CLOUD_WIND_COL;
			return colpara;
		}
	}

	colpara.colID = COL_ID::CLOUD_WIND_COL;
	return colpara;
}



CollisionParameter Actor::BoundarySphere_Capsule(const Actor& other) const{
	CollisionParameter colpara;

	Capsule tornado;
	tornado.startPos = Matrix4::GetPosition(other.parameter.mat);
	tornado.endPos = tornado.startPos + parameter.height;
	tornado.radius = other.parameter.radius;

	Sphere island;
	island.position = Matrix4::GetPosition(parameter.mat);
	island.radius = parameter.radius;

	colpara = Collisin::GetInstace().PushedBack_SphereCapsule(island, tornado);

	return colpara;
}

CollisionParameter Actor::PlayerCastleLine_vs_Cloud(const Actor& other) const
{
	Actor* player;
	CollisionParameter colpara;
		world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
			player = const_cast<Actor*>(&other);
	});
		std::vector<Vector3> boons = static_cast<Player*>(player)->ReturnBonePosStorage();
		Vector3 topPlayerPos = boons[0];
		Vector3 endPlayerPos = boons[boons.size()-1];
		int boonCount = 0;
		int boonNum = 0;
		
	//Cloud
		Sphere cloudSphere;
		cloudSphere.position = Matrix4::GetPosition(other.parameter.mat);
		cloudSphere.radius = other.parameter.radius;
	//PlayerBoon　プレイヤーの頭としっぽ
		Line toTopLine;
		toTopLine.startPos = topPlayerPos;
		toTopLine.endPos = parameter.mat.GetPosition();
		Line toEndLine;
		toEndLine.startPos = endPlayerPos;
		toEndLine.endPos = parameter.mat.GetPosition();
		
		if (Collisin::GetInstace().SegmentSphere(toTopLine, cloudSphere).colFlag)
		//if (Collisin::GetInstace().SegmentSphere(toEndLine, cloudSphere).colFlag)
		{
			colpara.colFlag = true;
			colpara.colAll = true;
		}
	colpara.colID = COL_ID::PLAYERTOCASTLELINE_CLOUD_COL;
	return colpara;
}

// 後で削除
// 線と箱の当たり判定
//CollisionParameter Actor::SegmentBoxAABB(const Actor& other) const{
//	CollisionParameter colpara;
//	HITRESULT_LINE result;
//
//	/* LineData */
//	Vector3 startPos, endPos; 
//
//	/*BoxData  */
//	Vector3 min, max;
//
//	result = HitCheck_Line_Cube(startPos, endPos, min, max);
//	colpara.colFlag = result.HitFlag;
//	colpara.colPos	= result.Position;
//
//	return colpara;
//}
//
//// 線と球の当たり判定
//CollisionParameter Actor::SegmentSphere(const Actor& other) const{
//	CollisionParameter colpara;
//
//	/* LineDara */
//	Vector3 startPos, endPos;
//
//	/* SphereData */
//	Vector3 sPos	= Matrix4::GetPosition(other.parameter.mat);
//	float	radius	= other.parameter.radius;
//
//	if (HitCheck_Line_Sphere(startPos, endPos, sPos, radius)) colpara.colFlag = true;
//
//	return colpara;
//}
//
//
//// 球と球のあたり判定
//CollisionParameter Actor::SphereSphere(const Actor& other) const{
//	CollisionParameter colpara;
//	if (Vector3::Distance(Matrix4::GetPosition(parameter.mat), Matrix4::GetPosition(other.parameter.mat))
//		< (parameter.radius + other.parameter.radius))colpara.colFlag = true;
//	return colpara;
//}
//
//// 球とカプセルの当たり判定
//CollisionParameter Actor::SphereCapsule(const Actor& other) const{
//	CollisionParameter colpara;
//
//	/* SphereData */
//	Vector3 sPos	= Matrix4::GetPosition(parameter.mat);
//	float	sRadius	= parameter.radius;
//
//	/* CapsuleData */
//	Vector3 startPos, endPos;
//	float cRadius = other.parameter.radius;
//	
//
//	if (HitCheck_Sphere_Capsule(sPos, sRadius, startPos, endPos, cRadius)) colpara.colFlag = true;
//
//	return colpara;
//}
//
//
//// カプセルとカプセルの当たり判定
//CollisionParameter Actor::CapsuleCapsule(const Actor& other) const{
//	CollisionParameter colpara;
//	Capsule c1, c2;
//
//	/* thisData */
//	c1.startPos = Matrix4::GetPosition(parameter.mat);
//	c1.endPos = c1.startPos + Matrix4::GetScale(parameter.mat) * Vector3::Up;
//	c1.radius = parameter.radius;
//
//	/* otherData */
//	c2.startPos = Matrix4::GetPosition(other.parameter.mat);
//	c2.endPos = c2.startPos + Matrix4::GetScale(other.parameter.mat)  * Vector3::Up;
//	c2.radius = other.parameter.radius;
//
//	if (HitCheck_Capsule_Capsule(
//		c1.startPos, c1.endPos, c1.radius,
//		c2.startPos, c2.endPos, c2.radius)) colpara.colFlag = true;
//
//	return colpara;
//}
//
//// カプセルと点の当たり判定
//CollisionParameter Actor::CapsulePoint(const Actor& other) const{
//	CollisionParameter colpara;
//
//	/* CapsuleData */
//	Vector3 startPos, endPos;
//
//	float length = Segment_Point_MinLength(startPos, endPos, Matrix4::GetPosition(other.parameter.mat));
//	if (length <= parameter.radius) colpara.colFlag = true;
//
//	return colpara;
//}
//
//// カプセルとAABBの当たり判定	（カプセルの半径より辺の間隔が長い場合は無効 ※Tornadoの高さをほぼ無限とする）
//CollisionParameter Actor::CapsuleAABBSegment(const Actor& other)const
//{
//	CollisionParameter colpara;
//
//	/* CapsuleData */
//	Capsule c;
//	c.startPos	= Matrix4::GetPosition(parameter.mat) * Vector3(1, 0, 1) - Vector3::Up * 100;
//	c.endPos	= c.startPos + Matrix4::GetScale(parameter.mat) * Vector3::Up * 100;
//	c.radius	= parameter.radius;
//
//	/* BoxData */
//	// √2をかけて当たり判定のかさましをしておく（45度回転を想定）
//	Vector3 min, max;
//	min = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 1)) / 2 * sqrtf(2);
//	max = Matrix4::GetPosition(other.parameter.mat) + (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 2, 1)) / 2 * sqrtf(2);
//	Vector3 sideData[4];
//	sideData[0] = Vector3::Zero;
//	sideData[1] = Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 0) * sqrtf(2);
//	sideData[2] = Matrix4::GetScale(other.parameter.mat) * Vector3(0, 1, 0) * sqrtf(2);
//	sideData[3] = Matrix4::GetScale(other.parameter.mat) * Vector3(0, 0, 1) * sqrtf(2);
//
//	Vector3 v, v2;
//	float length;
//	for (int i = 1; i <= 3; i++)
//	{
//		v = max - sideData[i];
//
//		length =
//			Segment_Segment_MinLength(
//			c.startPos, c.endPos,
//			max, v);
//
//		if (length <= parameter.radius)
//		{
//			colpara.colFlag = true;
//			break;
//		}
//	}
//
//	if (!colpara.colFlag)
//	{
//		for (int i = 0; i <= 3; i++)
//		{
//			for (int j = 1; j <= 3; j++)
//			{
//				if (colpara.colFlag) break;
//
//				if (i != j)
//				{
//					v = min + sideData[i];
//					v2 = v + sideData[j];
//					length =
//						Segment_Segment_MinLength(
//						c.startPos, c.endPos,
//						v, v2);
//
//					if (length <= parameter.radius)	
//						colpara.colFlag = true;
//				}
//			}
//		}
//	}
//
// 	return colpara;
//}
//
//
//// モデルと線分の当たり判定
//CollisionParameter Actor::ModelLine(const Actor& other) const{
//	CollisionParameter colpara;
//	MV1_COLL_RESULT_POLY HitPoly;
//
//	/* 線分データ */
//	Vector3 startPos, endPos;
//	startPos	= Matrix4::GetPosition(parameter.mat) - Vector3::Up * 300;
//	endPos		= startPos + Matrix4::GetScale(parameter.mat) * Vector3::Up;
//
//	HitPoly = MV1CollCheck_Line(0, 0, startPos, endPos);
//	if (HitPoly.HitFlag) colpara.colPos = HitPoly.HitPosition;
//
//	return colpara;
//}
//
//// モデルと球の当たり判定
//CollisionParameter Actor::ModelSphere(const Actor& other) const{
//	CollisionParameter colpara;
//	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
//
//	/* SphereData */
//	Vector3 center	= Matrix4::GetPosition(parameter.mat);
//	float radius	= parameter.radius;
//	
//	HitPolyDim = MV1CollCheck_Sphere(0, 0, center, radius);
//	if (HitPolyDim.HitNum >= 1) colpara.colFlag = true;
//
//	MV1CollResultPolyDimTerminate(HitPolyDim);
//	return colpara;
//}
//
//// モデルとカプセルの当たり判定
//CollisionParameter Actor::ModelCapsule(const Actor& other) const{
//	CollisionParameter colpara;
//	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
//
//	/* CapsuleData */
//	Vector3 height, startPos, endPos;
//	float radius;
//	startPos = Matrix4::GetPosition(parameter.mat);
//	endPos = startPos + height;
//	radius = parameter.radius;
//
//	HitPolyDim = MV1CollCheck_Capsule(0, 0, startPos, endPos, radius);
//	if (HitPolyDim.HitNum >= 1) colpara.colFlag = true;
//
//	MV1CollResultPolyDimTerminate(HitPolyDim);
//	return colpara;
//}
//
//// 円柱と箱の当たり判定
//CollisionParameter Actor::CylinderBox(const Actor& other) const{
//	CollisionParameter colpara;
//
//	/* 円柱データ */
//	// 円柱の軸と底面の交差する２点
//	Vector3 TopPos		= Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
//	Vector3 BottomPos	= Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
//	// ２点間のベクトル
//	float L = Vector3::Distance(TopPos, BottomPos);
//
//	/* 箱データ */
//	// 箱の大きさを取得
//	Vector3 BoxScale = Matrix4::GetScale(other.parameter.mat);
//	// 回転角を取得
//	Vector3 rotate = Matrix4::GetRotate(other.parameter.mat);
//	rotate = rotate * 180 / PI;
//	
//	// 箱の分割数を算出
// 	Vector3 split;
//	split.x = (int)(BoxScale.x / parameter.radius) + 1;
//	split.z = (int)(BoxScale.z / parameter.radius) + 1;
//	split.y = (int)(BoxScale.y / L) + 1;
//	if (split.x <= 1) split.x = 2;
//	if (split.y <= 1) split.y = 2;
//	if (split.z <= 1) split.z = 2;
//
//	// 辺の長さを設定
//	Vector3 side;
//	side.x = BoxScale.x / split.x;
//	side.y = BoxScale.y / split.y;
//	side.z = BoxScale.z / split.z;
//
//	// 基準点
//	//Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) / 2);						// オブジェクトの中心（Unity方式）
//	Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 1) / 2);	// モデルの底面中心
//
//	// 箱の点の保存
//	std::list<Vector3> points;
//	for (int z = 0; z <= split.z; z++)
//	{
//		for (int y = 0; y <= split.y; y++)
//		{
//			for (int x = 0; x <= split.x; x++)
//			{
//				if ((x == 0 || x == split.x) || (y == 0 || y == split.y) || (z == 0 || z == split.z))
//				{
//					Vector3 point = p + Vector3(side.x * x, side.y * y, side.z * z);
//
//					Vector3 aaa = point - Matrix4::GetPosition(other.parameter.mat);
//
//					// 座標変換
//					auto temp =
//						Matrix4::Translate(-aaa) *
//						Matrix4::RotateZ(rotate.z) *
//						Matrix4::RotateX(rotate.x) *
//						Matrix4::RotateY(rotate.y) *
//						Matrix4::Translate(Matrix4::GetPosition(other.parameter.mat));
//
//					points.push_back(Matrix4::GetPosition(temp));
//				}
//			}
//		}
//	}
//
//	// 頂点と円柱の当たり判定
//	for each (Vector3 p in points)
//	{
//		float S1 = Vector3::Distance(TopPos, p);
//		float S2 = Vector3::Distance(BottomPos, p);
//
//		float l = (S1 * S1 - L * L - S2 * S2) / (-2 * L);
//
//		if (!(l < 0.0f || l > L))
//		{
//			// 半径と線分を比較
//			auto qq = S2 * S2 - l * l;
//			if (qq <= parameter.radius * parameter.radius)	colpara.colFlag = true;
//		}
//	}
//
//	points.clear();
//	return colpara;
//
//	
//}

ActorParameter Actor::GetParameter() const
{
	return parameter;
}