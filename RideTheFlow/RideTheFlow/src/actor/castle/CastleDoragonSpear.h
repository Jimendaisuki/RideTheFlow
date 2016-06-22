#ifndef CASTLEDORAGONSPEAR_H_
#define CASTLEDORAGONSPEAR_H_

#include "../Actor.h"
#include <memory>
#include "castle.h"
class CastleDoragonSpear :public Actor, public std::enable_shared_from_this<CastleDoragonSpear>
{
public:
	CastleDoragonSpear(IWorld& world, Vector3 position/*, Castle &_castle*/,Actor& _parent,float rotateY);
	~CastleDoragonSpear();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Castle *castle;
	Matrix4 tubeMat;
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 startPos;
	Vector3 endPos;
	Vector3 tubePos;
	//ƒ^ƒCƒ€ŠÖŒW
	float coolTimer;
	float preparationTimer;
	float spearStopTimer;
	float spearAttackTimer;

	float mRotateY;
	bool playerWithin;
	bool attackSpear;
	bool endAttack;

};
#endif