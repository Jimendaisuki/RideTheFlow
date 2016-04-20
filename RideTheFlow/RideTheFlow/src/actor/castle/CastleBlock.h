#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"

class CastleBlock :public Actor
{
public:
	CastleBlock(IWorld& world, Vector3& position_, const float& risingSpeed_);
	~CastleBlock();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	float tornadeRadius;
	float tornadeSpeed;
	float risingSpeed;

	Vector3 scale;
	Vector3 position;
	Vector3 rotate;

	//回転によって加えられる座標量
	Vector3 tornadeAddPosition;
	float timer;
};