#pragma once
#include "Actor.h"
#include "../math/Vector3.h"

class AnimTestActor :public Actor
{
public:
	AnimTestActor(IWorld& world);
	~AnimTestActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
	float animetime;
};