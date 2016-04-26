#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"

class Castle : public Actor
{
public:
	Castle(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, float parSecondAttack, float attackRange);
	~Castle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Matrix4 playerMat;
	Vector3 mPosition;
	float mParSecondAttack;
	float mAttackRange;
	float time;
};