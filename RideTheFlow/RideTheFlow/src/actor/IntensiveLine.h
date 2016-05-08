#pragma once
#include "Actor.h"

class IntensiveLine : public Actor
{
public:
	IntensiveLine(IWorld& world, float angle);
	~IntensiveLine();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara);

private:
	Vector2	position;
	Vector2 velocity;
	float	speed;
	float	rotate;
	float	alpha;
	float	alphaTime;
};