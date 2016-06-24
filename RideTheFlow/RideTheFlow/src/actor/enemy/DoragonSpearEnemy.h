#ifndef DORAGONSPEARENEMY_H_
#define DORAGONSPEARENEMY_H_

#include "../Actor.h"
#include <memory>
#include "ShipEnemy.h"
class DoragonSpearEnemy :public Actor, public std::enable_shared_from_this<DoragonSpearEnemy>
{
public:
	DoragonSpearEnemy(IWorld& world, Vector3 position,ShipEnemy& se,Actor& _parent);
	~DoragonSpearEnemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
	bool AttackSpear()
	{
		return attackSpear;
	}
private:
	ShipEnemy* mSe;
	Matrix4 tubeMat;

	Vector3 mPosition;
	Vector3 mScale;
	Vector3 startPos;
	Vector3 endPos;

	//ƒ^ƒCƒ€ŠÖŒW
	float coolTimer;
	float preparationTimer;
	float spearStopTimer;
	float spearAttackTimer;

	bool playerWithin;
	bool attackSpear;
	bool endAttack;

};
#endif