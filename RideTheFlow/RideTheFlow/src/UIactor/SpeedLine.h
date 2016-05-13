#pragma once
#include "UIActor.h"
#include "../math/Vector3.h"

class SpeedLine : public UIActor
{
public:
	SpeedLine(IWorld& world, float angle);
	SpeedLine(IWorld& world, float angle, Vector3 directionPosition);
	SpeedLine(IWorld& world, Vector2 position, Vector2 velocity, float rotate);
	~SpeedLine();
	virtual void Update() override;
	virtual void Draw() const override;

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