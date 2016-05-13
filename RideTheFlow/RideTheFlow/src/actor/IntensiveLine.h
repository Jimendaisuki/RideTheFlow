#pragma once
#include "Actor.h"

class IntensiveLine : public Actor
{
public:
	IntensiveLine(IWorld& world, float angle);
	IntensiveLine(IWorld& world, float angle, Vector3 directionPosition);
	IntensiveLine(IWorld& world, Vector2 position, Vector2 velocity, float rotate);
	~IntensiveLine();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara);

private:
	Vector2	position;
	Vector2 velocity;
	Vector2 scale;
	float	speed;
	float	rotate;
	float	alpha;
	float	alphaTime;

	Vector2 Direction;
};