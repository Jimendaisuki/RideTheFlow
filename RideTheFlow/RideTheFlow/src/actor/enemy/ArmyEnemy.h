
#ifndef ARMYENEMY_H_
#define ARMYENEMY_H_

#include "../Actor.h"
#include <memory>
#include "../Player.h"
class ArmyEnemy : public Actor, public std::enable_shared_from_this<ArmyEnemy>
{
public:
	ArmyEnemy(IWorld& world, Vector3 position);
	~ArmyEnemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Player* player;
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 toPoint;
	Vector3 rotate;

	float downTime;
	float mSecondAttack;
	float mArrowNumber;
	
	float playerAngle;

	float attackTime;
	float attackRag;
	int arrowCount;
	bool isLook;

};

#endif