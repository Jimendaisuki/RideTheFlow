#pragma once
#include "Actor.h"
#include "../math/Vector3.h"
#include <memory>

class Player :public Actor, public std::enable_shared_from_this<Player>
{
public:
	Player(IWorld& world);
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	void ParameterDraw()const;
	Vector3 position;
	float upAngle, leftAngle;
	float speedRegulation;
	int boneSelect;
};