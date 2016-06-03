#ifndef SHIPENEMY_H_
#define SHIPENEMY_H_

#include "../Actor.h"
#include <memory>

class ShipEnemy :public Actor, public std::enable_shared_from_this<ShipEnemy>
{
public:
	ShipEnemy(IWorld& world, Vector3 position);
	~ShipEnemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 mPosition;
	Vector3 rotate;
	Matrix4 playerMat;

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