#pragma once
#include "../AllInclude.h"
#include "ActorID.h"
#include "../math/Matrix4.h"
#include "../math/Vector3.h"
#include "../math/Vector3Utility.h"
#include "../math/MatrixUtility.h"

struct ActorParameter
{
	ACTOR_ID id;
	Matrix4 matrix;
	bool isDead;
	float radius;
};

class Actor{
public:
	Actor();
	~Actor();
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	void Collide(Actor& other);
	bool IsCollide(const Actor& other)const;
	virtual bool IsDead() const{ return parameter.isDead; }

protected:
	virtual void OnCollide(Actor& other) = 0;
	ActorParameter parameter;
};