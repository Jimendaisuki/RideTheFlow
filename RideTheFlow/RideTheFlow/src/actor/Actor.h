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
	Matrix4 mat;
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
	//球と球のあたり判定
	CollisionParameter SphereSphere(const Actor& other)const;
	// カプセルとカプセルの当たり判定
	CollisionParameter CapsuleCapsule(const Actor& other)const;
	// 円柱と箱の当たり判定
	CollisionParameter CylinderBox(const Actor& other)const;
protected:
	virtual void OnCollide(Actor& other, CollisionParameter colpara) = 0;
	ActorParameter parameter;
	IWorld& world;
};