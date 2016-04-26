#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include "../../math/Vector2.h"
#include <memory>

class Tornado : public Actor, public std::enable_shared_from_this<Tornado>
{
public:
	Tornado(IWorld& world, Vector3 position, Vector2 scale, Vector3 velocity);
	~Tornado();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
	Vector3 velocity;
	Vector3	rotate;
	Vector3	scale;

	float	ACTIVITYTIME;
	float	GRAVITY;
	float	speed;

	bool	isHit;
};