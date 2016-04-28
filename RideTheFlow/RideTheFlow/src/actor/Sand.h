#pragma once
#include "Actor.h"
#include "../math/Vector3.h"

class Sand :public Actor
{
public:
	Sand(IWorld& world);
	~Sand();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector2 drawPositions[20];
};