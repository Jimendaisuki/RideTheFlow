#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>

class Castle : public Actor, public std::enable_shared_from_this<Castle>
{
public:
	Castle(IWorld& world, Vector3 position);
	~Castle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 mScale;
	bool isLook;
	int arrowCount;
	float attackRag;
	float mAttackTime;
	float mSecondAttack;
	float mArrowNumber;
};