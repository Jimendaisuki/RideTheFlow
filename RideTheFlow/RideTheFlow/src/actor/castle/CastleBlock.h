#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"

class CastleBlock :public Actor
{
public:
	CastleBlock(IWorld& world, Vector3& position_);
	~CastleBlock();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 tornadePos;
	Vector3 tornadeMove;
	float tornadeAddRadius;
	float tornadeRadius;
	float tornadeSpeed;
	float tornadeDegree;
	float risingSpeed;
	float risingAddSpeed;

	Vector3 scale;
	Vector3 position;
	Vector3 rotate;

	//回転によって加えられる座標量
	Vector3 tornadeAddPosition;
	float timer;
};