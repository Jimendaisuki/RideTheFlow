#ifndef CASTLECANNON_H_
#define CASTLECANNON_H_

#include "../Actor.h"
#include <memory>
#include "castle.h"
class CastleCannon :public Actor, public std::enable_shared_from_this<CastleCannon>
{
public:
	CastleCannon(IWorld& world, Vector3 position,Castle& castle,float rotateY,float scale);
	~CastleCannon();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Castle* castle;
	Matrix4 playerMat;
	Vector3 mPosition;

	float mScale;
	float mRotateY;
	float playerDot;
	float backDot;
	float angle;
	float mScaleFloat;
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