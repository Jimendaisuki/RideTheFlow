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
	colFunc[COL_ID::TORNADO_ENEMY_COL] = std::bind(&Actor::Tornado_vs_Enemy, this, std::placeholders::_1);

	colFunc[COL_ID::SPHERE_CAPSULE] = std::bind(&Actor::BoundarySphere_Capsule, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_TORNADO_COL] = std::bind(&Actor::Player_vs_Tornado, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_WIND_COL] = std::bind(&Actor::Player_vs_Wind, this, std::placeholders::_1);
	colFunc[COL_ID::CLOUD_WIND_COL] = std::bind(&Actor::Cloud_vs_Wind, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYERTOCASTLELINE_CLOUD_COL] = std::bind(&Actor::PlayerCastleLine_vs_Cloud, this, std::placeholders::_1);
	colFunc[COL_ID::CLOUD_TORNADO_COL] = std::bind(&Actor::Cloud_vs_Tornado, this, std::placeholders::_1);
	colFunc[COL_ID::ARMYENEMY_STAGE_COL] = std::bind(&Actor::ArmyEnemy_vs_Stage, this, std::placeholders::_1);
	colFunc[COL_ID::BULLET_WIND_COL] = std::bind(&Actor::Bullet_vs_Wind, this, std::placeholders::_1);

	colFunc[COL_ID::PLAYER_SHIPENEMY_COL] = std::bind(&Actor::Player_vs_ShipEnemy, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_DORAGONSPEAR_COL] = std::bind(&Actor::Player_vs_DoragonSpear, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_DORAGONSPEAR_WITHIN_COL] = std::bind(&Actor::Player_vs_DoragonSpearWithin, this, std::placeholders::_1);
	colFunc[COL_ID::CASTLE_CASTLE_COL] = std::bind(&Actor::Castle_vs_Castle, this, std::placeholders::_1);
	colFunc[COL_ID::SHIP_ISLAND_COL] = std::bind(&Actor::Ship_vs_Island, this, std::placeholders::_1);
	colFunc[COL_ID::ENEMY_WIND_COL] = std::bind(&Actor::Enemy_vs_Wind, this, std::placeholders::_1);
	colFunc[COL_ID::CASTLE_WIND_COL ] = std::bind(&Actor::Castle_vs_Wind, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_CASTLE_COL] = std::bind(&Actor::Player_vs_Castle, this, std::placeholders::_1);
	colFunc[COL_ID::MASTERCASTLE_CASTLE_COL] = std::bind(&Actor::MasterCastle_vs_Castle, this, std::placeholders::_1);
	colFunc[COL_ID::SHIP_SHIP_COL] = std::bind(&Actor::Ship_vs_Ship, this, std::placeholders::_1);
	colFunc[COL_ID::BULLET_NOBULLETAREA_COL] = std::bind(&Actor::Bullet_vs_NoBulletArea, this, std::placeholders::_1);
	colFunc[COL_ID::CASTLE_AIRGUN_COL] = std::bind(&Actor::Castle_vs_AirGun, this, std::placeholders::_1);
	colFunc[COL_ID::ENEMY_AIRGUN_COL] = std::bind(&Actor::Enemy_vs_AirGun, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_LAND_COL] = std::bind(&Actor::Player_vs_land, this, std::placeholders::_1);
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
	//対移動制限
	ModelData range;
	range.MHandle = Model::GetInstance().GetHandle(MODEL_ID::STAGE_ACTION_RANGE_MODEL);
	range.MFrameIndex = -1;
	bool rangeflag = false;

	colpara = Collisin::GetInstace().ModelSphere(range, sphere);
	/* ResultData */
	while (colpara.colFlag){
		sphere.position += colpara.colPos.Normalized() * 1.0f;
		rangeflag = true;
		colpara = Collisin::GetInstace().ModelSphere(range, sphere);
	}

	//対ステージ
	ModelData stage;
	stage.MHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE);
	stage.MFrameIndex = -1;
	bool stageflag = false;

	colpara = Collisin::GetInstace().ModelSphere(stage, sphere);
	/* ResultData */
	while (colpara.colFlag){
		sphere.position += colpara.colPos.Normalized() * 1.0f;
		stageflag = true;
		colpara = Collisin::GetInstace().ModelSphere(stage, sphere);
	}

	colpara.colPos = sphere.position;
	colpara.colID = COL_ID::PLAYER_STAGE_COL;
	if (stageflag || rangeflag)
		colpara.colFlag = true;

	return colpara;
}

CollisionParameter Actor::Player_vs_land(const Actor& other) const
{
	CollisionParameter colpara;
	Sphere sphere;
	sphere.position = parameter.mat.GetPosition();
	sphere.radius = parameter.radius;

	//対ステージ
	ModelData stage;
	stage.MHandle = Model::GetInstance().GetHandle(MODEL_ID::ISLE_1_MODEL);
	stage.MFrameIndex = -1;
	bool stageflag = false;

	colpara = Collisin::GetInstace().ModelSphere(stage, sphere);
	/* ResultData */
	if (colpara.colFlag)
	{

		while (colpara.colFlag){
			sphere.position += colpara.colPos.Normalized() * 1.0f;
			stageflag = true;
			colpara = Collisin::GetInstace().ModelSphere(stage, sphere);
		}

		colpara.colPos = sphere.position;
		colpara.colID = COL_ID::PLAYER_LAND_COL;
		if (stageflag)
		{
			colpara.colFlag = true;
			return colpara;
		}
	}
	if (!colpara.colFlag)
	{
		ModelData stage1;
 		stage1.MHandle = Model::GetInstance().GetHandle(MODEL_ID::ISLE_2_MODEL);
		stage1.MFrameIndex = -1;
		stageflag = false;
		colpara = Collisin::GetInstace().ModelSphere(stage1, sphere);
		/* ResultData */
		while (colpara.colFlag){
			sphere.position += colpara.colPos.Normalized() * 1.0f;
			stageflag = true;
			colpara = Collisin::GetInstace().ModelSphere(stage1, sphere);
		}

		colpara.colPos = sphere.position;
		colpara.colID = COL_ID::PLAYER_LAND_COL;
		if (stageflag)
		{
			colpara.colFlag = true;
			return colpara;
		}
	}
	if (!colpara.colFlag)
	{
		sphere.position = parameter.mat.GetPosition();
		sphere.radius = parameter.radius;
		ModelData stage2;
		stage2.MHandle = Model::GetInstance().GetHandle(MODEL_ID::ISLE_3_MODEL);
		stage2.MFrameIndex = -1;
		stageflag = false;

		colpara = Collisin::GetInstace().ModelSphere(stage2, sphere);
		/* ResultData */
		while (colpara.colFlag){
			sphere.position += colpara.colPos.Normalized() * 1.0f;
			stageflag = true;
			colpara = Collisin::GetInstace().ModelSphere(stage2, sphere);
		}

		colpara.colPos = sphere.position;
		colpara.colID = COL_ID::PLAYER_LAND_COL;
		if (stageflag)
		{
			colpara.colFlag = true;
			return colpara;
		}
	}
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

	//Capsule player;
	//std::vector<Vector3> playerBonePos = static_cast<Player*>(const_cast<Actor*>(this))->ReturnBonePosStorage();

	//for (int i = 0; i < playerBonePos.size();i+=6) {
	//	if (i >= playerBonePos.size())i = playerBonePos.size() - 1;
	//	/* PlayerData */
	//	Sphere player;
	//	player.position = playerBonePos[i];
	//	player.radius = parameter.radius;
	//	/* ResultData */
	//	colpara = Collisin::GetInstace().SphereSphere(player, bullet);
	//	if (colpara.colFlag){
	//		break;
	//	}
	//}

	std::vector<Vector3> playerBonePos = static_cast<Player*>(const_cast<Actor*>(this))->ReturnBonePosStorage();
	for (int i = 0; i < playerBonePos.size();) {
		/* PlayerData */
		Capsule player;
		player.startPos = playerBonePos[i];
		i += 6;
		if (i >= playerBonePos.size()) {
			i = playerBonePos.size() - 1;
		}
		player.endPos = playerBonePos[i];
		player.radius = parameter.radius;
		/* ResultData */
		colpara = Collisin::GetInstace().SphereCapsule(bullet,player);
		if (colpara.colFlag){
			break;
		}

		if (i == playerBonePos.size() - 1)break;
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

CollisionParameter Actor::Player_vs_ShipEnemy(const Actor& other) const
{
	Actor* player;
	CollisionParameter colpara;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		player = const_cast<Actor*>(&other);
	});
	std::vector<Vector3> playerBonePos = static_cast<Player*>(player)->ReturnBonePosStorage();

	//ShipEnemy
	Sphere shipEnemy;
	shipEnemy.position = parameter.mat.GetPosition() + parameter.mat.GetUp().Normalized()*parameter.radius;
	shipEnemy.radius = parameter.radius;

	for (int i = 0; i < playerBonePos.size();) {
		/* PlayerData */
		Capsule player;
		player.startPos = playerBonePos[i];
		i += 6;
		if (i >= playerBonePos.size()) {
			i = playerBonePos.size() - 1;
		}
		player.endPos = playerBonePos[i];
		player.radius = parameter.radius;
		/* ResultData */
		colpara = Collisin::GetInstace().SphereCapsule(shipEnemy, player);
		if (colpara.colFlag) {
			break;
		}

		if (i == playerBonePos.size() - 1)break;
	}
	colpara.colID = COL_ID::PLAYER_SHIPENEMY_COL;
	return colpara;
}

CollisionParameter Actor::Player_vs_DoragonSpear(const Actor& other) const
{
	Actor* player;
	CollisionParameter colpara;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		player = const_cast<Actor*>(&other);
	});
	std::vector<Vector3> playerBonePos = static_cast<Player*>(player)->ReturnBonePosStorage();
	Capsule spear;
	spear.startPos = other.parameter.mat.GetPosition() - other.parameter.mat.GetLeft().Normalized()*10.0f;
	spear.endPos = other.parameter.mat.GetPosition() + other.parameter.mat.GetLeft().Normalized()*30.0f;
	spear.radius = other.parameter.radius;

	for (int i = 0; i < playerBonePos.size();) {
		/* PlayerData */
		Capsule player;
		player.startPos = playerBonePos[i];
		i += 6;
		if (i >= playerBonePos.size()) {
			i = playerBonePos.size() - 1;
		}
		player.endPos = playerBonePos[i];
		player.radius = parameter.radius;
		/* ResultData */
		colpara = Collisin::GetInstace().CapsuleCapsule(spear, player);
		if (colpara.colFlag) {
			break;
		}

		if (i == playerBonePos.size() - 1)break;
	}

	colpara.colID = COL_ID::PLAYER_DORAGONSPEAR_COL;
	return colpara;
}

CollisionParameter Actor::Player_vs_DoragonSpearWithin(const Actor& other)const
{
	Actor* player;
	CollisionParameter colpara;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		player = const_cast<Actor*>(&other);
	});
	std::vector<Vector3> boons = static_cast<Player*>(player)->ReturnBonePosStorage();

	Capsule spear;
	spear.startPos = parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*30.0f;
	spear.endPos = parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*70.0f;
	spear.radius = parameter.radius;
	for (int i = 0; i < boons.size(); i += 5)
	{
		if (i >= boons.size())i = boons.size() - 1;		Sphere playerSphere;
		playerSphere.position = boons[i];
		playerSphere.radius = player->parameter.radius;
		colpara = Collisin::GetInstace().SphereCapsule(playerSphere, spear);
		if (colpara.colFlag)
			break;
	}
	colpara.colID = COL_ID::PLAYER_DORAGONSPEAR_WITHIN_COL;
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
	stage.MHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE);
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
	colpara.colVelosity = other.parameter.velocity;
	colpara.colPos = tornado.startPos;

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

CollisionParameter Actor::Tornado_vs_Enemy(const Actor& other) const{
	CollisionParameter colpara;

	Sphere enemy;
	enemy.position = Matrix4::GetPosition(parameter.mat);
	enemy.radius = parameter.radius;

	Capsule tornado;
	tornado.startPos = Matrix4::GetPosition(other.parameter.mat);
	tornado.endPos = tornado.startPos + other.parameter.height;
	tornado.radius = other.parameter.radius;

	colpara = Collisin::GetInstace().SphereCapsule(enemy, tornado);

	colpara.colID = COL_ID::TORNADO_ENEMY_COL;
	colpara.colVelosity = other.parameter.velocity;
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
	colpara.colID = COL_ID::TORNADO_ISLAND_COL;
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
		 if (Collisin::GetInstace().SegmentSphere(toEndLine, cloudSphere).colFlag)
		{
			colpara.colFlag = true;
			colpara.colAll = true;
		}
	colpara.colID = COL_ID::PLAYERTOCASTLELINE_CLOUD_COL;
	return colpara;
}

CollisionParameter Actor::ArmyEnemy_vs_Stage(const Actor& other)const
{
	CollisionParameter colpara;
	Line armyEnemy;
	armyEnemy.startPos = parameter.mat.GetPosition();
	armyEnemy.endPos = parameter.mat.GetPosition() - Vector3::Down*parameter.radius;

	ModelData stage;
	stage.MHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE);
	stage.MFrameIndex = -1;
	colpara = Collisin::GetInstace().ModelLine(stage, armyEnemy);
	colpara.colID = COL_ID::ARMYENEMY_STAGE_COL;
	return colpara;

}

CollisionParameter Actor::Bullet_vs_Wind(const Actor& other) const{
	CollisionParameter colpara;

	colpara = Cloud_vs_Wind(other);
	colpara.colID = COL_ID::BULLET_WIND_COL;

	return colpara;
}

CollisionParameter Actor::Castle_vs_Castle(const Actor& other) const
{
	CollisionParameter colpara;
	Sphere castle1;
	castle1.radius = parameter.radius;
	castle1.position = parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius, 0.0f);
	Sphere castle2;
	castle2.radius = other.parameter.radius;
	castle2.position = other.parameter.mat.GetPosition() + Vector3(0.0f, other.parameter.radius, 0.0f);

	colpara = Collisin::GetInstace().SphereSphere(castle1, castle2);
	colpara.colID = COL_ID::CASTLE_CASTLE_COL;

	if (&other == this)
	{
		colpara.colFlag = false;
	}

 	return colpara;
	
}
CollisionParameter Actor::MasterCastle_vs_Castle(const Actor& other) const
{
	CollisionParameter colpara;

	colpara = Castle_vs_Castle(other);
	colpara.colID = COL_ID::MASTERCASTLE_CASTLE_COL;
	return colpara;
}

CollisionParameter Actor::Ship_vs_Island(const Actor& other) const
{
	CollisionParameter colpara;
	Sphere shipEnemy;
	shipEnemy.position = parameter.mat.GetPosition() + parameter.mat.GetUp().Normalized()*parameter.radius;
	shipEnemy.radius = parameter.radius;
	Sphere isLand;
	isLand.position = other.parameter.mat.GetPosition();
	isLand.radius = other.parameter.radius;

	colpara = Collisin::GetInstace().SphereSphere(shipEnemy, isLand);
	colpara.colPos = other.GetParameter().mat.GetPosition();
	colpara.colID = COL_ID::SHIP_ISLAND_COL;
	return colpara;
}

CollisionParameter Actor::Enemy_vs_Wind(const Actor& other) const
{
	CollisionParameter colpara;
	colpara = Cloud_vs_Wind(other);
	colpara.colID = COL_ID::ENEMY_WIND_COL;
	return colpara;
}
CollisionParameter Actor::Castle_vs_Wind(const Actor& other) const
{
	CollisionParameter colpara;
	Sphere castle;
	castle.position = parameter.mat.GetPosition()+Vector3(0.0f,parameter.radius,0.0f);
	castle.radius = parameter.radius;

	WindFlow* w = static_cast<WindFlow*>(const_cast<Actor*>(&other));
	std::vector<Vector3> dashPositions = w->GetDashPositions();
	int dashPositionSize = dashPositions.size();
	Vector3 move = w->GetMoveVec();

	if (dashPositionSize < 2)
	{
		colpara.colID = COL_ID::CASTLE_WIND_COL;
		return colpara;
	}

	Capsule wind;
	wind.radius = other.parameter.radius;
	for (int i = 0; i < dashPositionSize; i++)
	{
		wind.startPos = dashPositions.at(i) + move;
		wind.endPos = wind.startPos;
		wind.endPos.y = other.parameter.height.y;
		colpara = Collisin::GetInstace().SphereCapsule(castle, wind);

		if (colpara.colFlag)
		{
			if (i == dashPositionSize - 1)
				colpara.colVelosity = Vector3::Normalize(dashPositions.at(i) - dashPositions.at(i - 1));
			else
				colpara.colVelosity = Vector3::Normalize(dashPositions.at(i + 1) - dashPositions.at(i));

			colpara.colID = COL_ID::CASTLE_WIND_COL;
			return colpara;
		}
	}
	colpara.colID = COL_ID::CLOUD_WIND_COL;
	return colpara;

}

CollisionParameter Actor::Player_vs_Castle(const Actor& other)const
{
	CollisionParameter colpara;
	CollisionParameter colpara2;
	Capsule castle;
	castle.startPos = other.parameter.mat.GetPosition();
	castle.endPos = castle.startPos + other.parameter.height;
	castle.radius = 80.0f;
	Sphere player;
	player.position = parameter.mat.GetPosition();
	player.radius = parameter.radius;

	Capsule masterCastle;
	masterCastle.startPos = other.parameter.mat.GetPosition();
	masterCastle.endPos = masterCastle.startPos+Vector3(0.0f,0.1f,0.0f);
	masterCastle.radius = 100.0f;


	colpara = Collisin::GetInstace().PushedBack_SphereCapsule(player, castle);
	colpara.colID = COL_ID::MASTERCASTLE_CASTLE_COL;

	if (colpara.colFlag)
	{
		player.position = colpara.colPos;
		colpara2 = Collisin::GetInstace().PushedBack_SphereCapsule(player, masterCastle);
		if (colpara2.colFlag)
		{
			colpara = colpara2;
			colpara.colID = COL_ID::MASTERCASTLE_CASTLE_COL;
			return colpara;
		}
		else
			return colpara;
	}
	colpara = Collisin::GetInstace().PushedBack_SphereCapsule(player, masterCastle);
	colpara.colID = COL_ID::MASTERCASTLE_CASTLE_COL;
	return colpara;
}

CollisionParameter Actor::Ship_vs_Ship(const Actor& other)const
{
	CollisionParameter colpara;
	Sphere ship1;
	ship1.radius = parameter.radius*3.0f;
	ship1.position = parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius, 0.0f);
	Sphere ship2;
	ship2.radius = other.parameter.radius*3.0f;
	ship2.position = other.parameter.mat.GetPosition() + Vector3(0.0f, other.parameter.radius, 0.0f);

	colpara = Collisin::GetInstace().SphereSphere(ship1, ship2);
	colpara.colID = COL_ID::SHIP_SHIP_COL;
	colpara.colPos = other.GetParameter().mat.GetPosition();

	if (&other == this)
	{
		colpara.colFlag = false;
	}
	return colpara;
}
CollisionParameter Actor::Bullet_vs_NoBulletArea(const Actor& other)const
{
	CollisionParameter colpara;
	Sphere bullet;
	bullet.radius = parameter.radius;
	bullet.position = parameter.mat.GetPosition();
	Sphere noBullet;
	noBullet.radius = other.parameter.radius;
	noBullet.position = other.parameter.mat.GetPosition();

	colpara = Collisin::GetInstace().SphereSphere(bullet, noBullet);
	colpara.colID = COL_ID::BULLET_NOBULLETAREA_COL;
	return colpara;
}

CollisionParameter Actor::Castle_vs_AirGun(const Actor& other) const
{
	CollisionParameter colpara;
	Sphere castle;
	castle.radius = parameter.radius;
	castle.position = parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius, 0.0f);
	Sphere airgun;
	airgun.radius = other.parameter.radius;
	airgun.position = other.parameter.mat.GetPosition();

	colpara = Collisin::GetInstace().SphereSphere(castle, airgun);
	colpara.colID = COL_ID::CASTLE_AIRGUN_COL;

	return colpara;
}
CollisionParameter Actor::Enemy_vs_AirGun(const Actor& other) const
{
	CollisionParameter colpara;
	Sphere ship;
	ship.radius = parameter.radius;
	ship.position = parameter.mat.GetPosition();
	Sphere airgun;
	airgun.radius = other.parameter.radius;
	airgun.position = other.parameter.mat.GetPosition();

	colpara = Collisin::GetInstace().SphereSphere(ship, airgun);
	colpara.colID = COL_ID::ENEMY_AIRGUN_COL;

	return colpara;
}


ActorParameter Actor::GetParameter() const
{
	return parameter;
}