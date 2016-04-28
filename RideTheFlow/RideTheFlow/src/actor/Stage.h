#pragma once
#include "Actor.h"
#include "../math/Vector3.h"

class Stage :public Actor
{
public:
	Stage(IWorld& world);
	~Stage();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
};