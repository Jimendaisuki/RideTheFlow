#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"

class Tornado : public Actor
{
public:
	Tornado(IWorld& world, Vector3 position, Vector3 velocity);
	~Tornado();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
	Vector3 velocity;
	Vector3	rotate;
	Vector3	scale;
};