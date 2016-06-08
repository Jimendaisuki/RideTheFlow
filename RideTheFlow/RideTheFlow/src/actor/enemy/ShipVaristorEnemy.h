#ifndef SHIPVARISTORENEMY_H_
#define SHIPVARISTORENEMY_H_

#include "../Actor.h"
#include <memory>
#include "ShipEnemy.h"

class ShipVaristorEnemy : public Actor, public std::enable_shared_from_this<ShipVaristorEnemy>
{
public:
	ShipVaristorEnemy(IWorld& world, Vector3 position, ShipEnemy& se, bool left, float rotateY);
	~ShipVaristorEnemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	void Attack();
private:
	ShipEnemy* mSe;
	Vector3 mPosition;
	Vector3 rotate;
	Matrix4 playerMat;
	float playerDot;

	float backDot;

	//çUåÇä÷åW
	float mSecondAttack;
	float mArrowNumber;
	float playerAngle;
	float attackAngle;
	float attackTime;
	float attackRag;
	int arrowCount;
	bool isLook;
	bool mLeft;
};

#endif