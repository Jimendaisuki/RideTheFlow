#pragma once
#include "Actor.h"
#include "../math/Vector3.h"

class Player :public Actor
{
public:
	Player(IWorld& world);
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
	float animetime;
};