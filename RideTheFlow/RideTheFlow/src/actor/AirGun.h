#pragma once
#include "Actor.h"
#include <vector>

class AirGun :public Actor
{
public:
	AirGun(IWorld& world, Vector3 position_, Vector3 velocity_);
	~AirGun();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Vector3 position;
	Vector3 velocity;
	float range;
	std::vector<Matrix4> rotates;
	std::vector<Matrix4> mats;
	float alpha;
};