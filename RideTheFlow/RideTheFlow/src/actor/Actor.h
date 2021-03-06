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

	CollisionParameter Player_vs_land(const Actor& other) const;
	/* 龍vs */
	// 龍と弾
	CollisionParameter Player_vs_Bullet(const Actor& other) const;
	CollisionParameter Player_vs_Tornado(const Actor& other) const;
	CollisionParameter Player_vs_Wind(const Actor& other) const;
	//竜と船の敵
	CollisionParameter Player_vs_ShipEnemy(const Actor& other) const;
	//龍と撃龍槍
	CollisionParameter Player_vs_DoragonSpear(const Actor& other) const;
	CollisionParameter Player_vs_DoragonSpearWithin(const Actor& other)const;

	CollisionParameter Player_vs_Castle(const Actor& other)const;
	/* 風圧vs */
	// 風圧と弾
	// 風圧と竜巻


	/* 竜巻vs */
	// 竜巻とステージの当たり判定
	CollisionParameter Tornado_vs_Stage(const Actor& other) const;
	// 竜巻と城の当たり判定
	CollisionParameter Tornado_vs_Castle(const Actor& other) const;
	// 竜巻と浮島の当たり判定
	CollisionParameter Tornado_vs_IsLand(const Actor& other) const;
	// 竜巻と風圧の当たり判定

	//竜巻と敵のあたり判定
	CollisionParameter Tornado_vs_Enemy(const Actor& other) const;

	/*  */
	CollisionParameter BoundarySphere_Capsule(const Actor& other)  const;

	// 雲と竜巻の当たり判定
	CollisionParameter Cloud_vs_Tornado(const Actor& other) const;
	// 雲と風の当たり判定(球 vs カプセルの集合)
	CollisionParameter Cloud_vs_Wind(const Actor& other) const;

	//城とプレイヤーを結んだ線と雲のあたり判定
	CollisionParameter PlayerCastleLine_vs_Cloud(const Actor& other) const;
	//軍隊とステージのあたり判定
	CollisionParameter ArmyEnemy_vs_Stage(const Actor& other)const;
	// 弾と風の当たり判定(球 vs カプセルの集合)
	CollisionParameter Bullet_vs_Wind(const Actor& other) const;

	//上の城と下の城のあたり判定 
	CollisionParameter Castle_vs_Castle(const Actor& other) const;
	//master城と城のあたり判定
	CollisionParameter MasterCastle_vs_Castle(const Actor& other) const;
	//船と浮島のあたり判定
	CollisionParameter Ship_vs_Island(const Actor& other) const;
	//風と敵のあたり判定
	CollisionParameter Enemy_vs_Wind(const Actor& other) const;
	//風と城のあたり判定
	CollisionParameter Castle_vs_Wind(const Actor& other) const;

	//船と船のあたり判定
	CollisionParameter Ship_vs_Ship(const Actor& other)const;
	//敵の攻撃と当たると攻撃が消えるエリア
	CollisionParameter Bullet_vs_NoBulletArea(const Actor& other)const;

	//城と空気砲
	CollisionParameter Castle_vs_AirGun(const Actor& other) const;
	//敵と空気砲
	CollisionParameter Enemy_vs_AirGun(const Actor& other) const;

	/* 後で削除
	// 線と箱の当たり判定
	CollisionParameter SegmentBoxAABB(const Actor& other)const;
	// 線と球の当たり判定
	CollisionParameter SegmentSphere(const Actor& other)const;
	// 球と球のあたり判定
	CollisionParameter SphereSphere(const Actor& other)const;
	// 球とカプセルの当たり判定
	CollisionParameter SphereCapsule(const Actor& other)const;
	// カプセルとカプセルの当たり判定
	CollisionParameter CapsuleCapsule(const Actor& other)const;
	// カプセルと点の当たり判定
	CollisionParameter CapsulePoint(const Actor& other)const;
	// カプセルとAABBの当たり判定
	CollisionParameter CapsuleAABBSegment(const Actor& other)const;
	// モデルと線分の当たり判定
	CollisionParameter ModelLine(const Actor& other)const;
	// モデルと球の当たり判定
	CollisionParameter ModelSphere(const Actor& other)const;
	// モデルとカプセルの当たり判定
	CollisionParameter ModelCapsule(const Actor& other)const;
	// 円柱と箱の当たり判定
	CollisionParameter CylinderBox(const Actor& other)const;
	*/


protected:
	virtual void OnCollide(Actor& other, CollisionParameter colpara) = 0;
	ActorParameter parameter;
	IWorld& world;

public:
	Actor* parent;
};