#ifndef ENEMY_GUN_H_
#define ENEMY_GUN_H_

#include "Actor.h"
#include "EnemyAttack.h"
class EnemyGun :public Actor
{
public:
	EnemyGun(IWorld& world);
	~EnemyGun();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 mDirection;

};

#endif