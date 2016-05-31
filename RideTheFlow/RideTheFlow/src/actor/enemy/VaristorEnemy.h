#ifndef VARISTORENEMY_H_
#define VARISTORENEMY_H_

#include "../Actor.h"
#include <memory>

class VaristorEnemy : public Actor, public std::enable_shared_from_this<VaristorEnemy>
{
public:
	VaristorEnemy(IWorld& world, Vector3 position);
	~VaristorEnemy();
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