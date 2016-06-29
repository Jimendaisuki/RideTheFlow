#ifndef SOLDIERENEMY_H_
#define SOLDIERENEMY_H_

#include "../Actor.h"
#include <memory>
#include "../castle/castle.h"
class SoldierEnemy : public Actor, public std::enable_shared_from_this<SoldierEnemy>
{
public:
	SoldierEnemy(IWorld& world, Vector3 position,Castle& castle,float rotateY,float scale);
	~SoldierEnemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Castle* mCastle;
	Matrix4 playerMat;
	Matrix4 cameraMat;
	Vector3 mPosition;
	Vector3 toPoint;
	float  mRotateY;

	float mSecondAttack;
	float mArrowNumber;

	float playerAngle;

	float attackTime;
	float attackRag;
	int arrowCount;
	bool isLook;
	float mScaleFloat;
	float mScale;

};

#endif