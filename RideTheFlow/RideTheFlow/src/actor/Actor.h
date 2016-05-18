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


	/* 龍vs */
	// 龍と弾
	CollisionParameter Player_vs_Bullet(const Actor& other) const;
	CollisionParameter Player_vs_Tornado(const Actor& other) const;

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

	/*  */
	CollisionParameter BoundarySphere_Capsule(const Actor& other)  const;

	// 雲と風の当たり判定(球 vs カプセルの集合)
	CollisionParameter Cloud_vs_Wind(const Actor& other) const;

	//城とプレイヤーを結んだ線と雲のあたり判定
	CollisionParameter PlayerCastleLine_vs_Cloud(const Actor& other) const;

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