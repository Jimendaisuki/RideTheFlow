#ifndef CANNONENEMY_H_
#define CANNONENEMY_H_

#include "../Actor.h"
#include <memory>

class CannonEnemy :public Actor, public std::enable_shared_from_this<CannonEnemy>
{
public:
	CannonEnemy(IWorld& world, Vector3 position);
	~CannonEnemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 mPosition;
	Vector3 rotate;
	Matrix4 playerMat;
	float playerDot;

	//çUåÇä÷åW
	float mSecondAttack;
	float mArrowNumber;
	float playerAngle;
	float attackTime;
	float attackRag;
	int arrowCount;
	bool isLook;


};

#endif