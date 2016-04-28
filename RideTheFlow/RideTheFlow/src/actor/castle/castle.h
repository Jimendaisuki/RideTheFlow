#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"

class Castle : public Actor
{
public:
	Castle(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, float secondAttack, float attackRange, int arrowNumber, float arrowAccuracy,float attackTime);
	~Castle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 randomTarget;
	Vector3 startPos;
	Vector3 endPos;
	float mSecondAttack;
	float mAttackRange;
	int mArrowNumber;
	int arrowCount;
	float mArrowAccuracy;
	float attackRag;
	float mAttackTime;
};