
#ifndef ARMYENEMY_H_
#define ARMYENEMY_H_

#include "../Actor.h"
#include <memory>

class ArmyEnemy : public Actor, public std::enable_shared_from_this<ArmyEnemy>
{
public:
	ArmyEnemy(IWorld& world, Vector3 position);
	~ArmyEnemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Matrix4 playerMat;
	Matrix4 cameraMat;
	Vector3 mPosition;

	float mSecondAttack;
	float mArrowNumber;
	
	float playerAngle;

	float attackTime;
	float attackRag;
	int arrowCount;
	float clor;
	bool isLook;
};

#endif