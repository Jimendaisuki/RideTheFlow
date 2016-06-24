#ifndef CASTLEVARISTOR_H_
#define CASTLEVARISTOR_H_

#include "../Actor.h"
#include <memory>
#include "castle.h"
class CastleVaristor :public Actor, public std::enable_shared_from_this<CastleVaristor>
{
public:
	CastleVaristor(IWorld& world, Vector3 position, Castle& castle, float rotateY);
	~CastleVaristor();
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