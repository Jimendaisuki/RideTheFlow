#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include "../../math/Vector2.h"
#include <memory>
#include "../particle/ParticleSystem.h"

#include "../particle/ParticleSystem.h"

class Tornado : public Actor, public ParticleSystem, public std::enable_shared_from_this<Tornado>
{
public:
	//=======Actor======//
	Tornado(IWorld& world, Vector3 position, Vector2 scale, Vector3 velocity, float radius_);
	~Tornado();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
	void SetVelocity(Vector3 vec) { velocity = vec; }

	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	Vector3 position;
	Vector3 velocity;
	Vector3	rotate;
	Vector3	scale;

	float	ACTIVITYTIME;
	float	GRAVITY;
	float	speed;
	float	radius;

	bool	isHit;

	float timer;
};