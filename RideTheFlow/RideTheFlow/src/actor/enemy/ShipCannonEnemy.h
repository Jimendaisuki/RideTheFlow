#ifndef SHIPCANNONENEMY_H_
#define SHIPCANNONENEMY_H_

#include "../Actor.h"
#include <memory>
#include "ShipEnemy.h"

class ShipCannonEnemy : public Actor, public std::enable_shared_from_this<ShipCannonEnemy>
{
public:
	ShipCannonEnemy(IWorld& world, Vector3 position, ShipEnemy& se, bool left, float rotateY);
	~ShipCannonEnemy();
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