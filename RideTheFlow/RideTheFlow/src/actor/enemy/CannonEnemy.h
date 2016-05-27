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
	Vector3 restRotate;
	Vector3 rotateVelocity;
	float test;


	//UŒ‚‚Ìs‚«‚Â‚­æŠÖŒW
	Matrix4 playerMat;
	Matrix4 cameraMat;
	Vector3 toPoint;

	//UŒ‚ŠÖŒW
	float mSecondAttack;
	float mArrowNumber;
	float playerAngle;
	float attackTime;
	float attackRag;
	int arrowCount;
	bool isLook;


};

#endif