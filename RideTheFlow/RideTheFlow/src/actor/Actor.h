#pragma once
#include "../AllInclude.h"
#include "ID.h"
#include "../graphic/Sprite.h"
#include <map>
#include <functional>

class IWorld;
struct CollisionParameter;

struct ActorParameter
{
	ACTOR_ID id;
	bool isDead;
	float radius;
};

class Actor{
public:
	Actor(IWorld& world_);
	~Actor();
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	void Collide(COL_ID id, Actor& other);
	virtual bool IsDead() const{ return parameter.isDead; }
	ActorParameter GetParameter();

private:
	std::map<COL_ID, std::function<CollisionParameter(const Actor&)>> colFunc;
	//‹…‚Æ‹…‚Ì‚ ‚½‚è”»’è
	CollisionParameter SphereSphere(const Actor& other)const;
protected:
	virtual void OnCollide(Actor& other, CollisionParameter colpara) = 0;
	ActorParameter parameter;
	IWorld& world;
};