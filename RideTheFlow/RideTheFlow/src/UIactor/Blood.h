#pragma once
#include "UIActor.h"
#include "../math/Vector3.h"

class Actor;

class Blood : public UIActor
{
public:
	Blood(IWorld& world, const Vector3 position, const Vector3 front);
	Blood(IWorld& world, const Vector3 position, const Actor& player_);
	~Blood();
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