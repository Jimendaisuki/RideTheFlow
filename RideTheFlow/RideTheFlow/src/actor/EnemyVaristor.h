#ifndef ENEMY_VARISTOR_H_
#define ENEMY_VARISTOR_H_

#include "Actor.h"
#include "EnemyAttack.h"

class EnemyVaristor:public Actor 
{
public:
	EnemyVaristor(IWorld& world);
	~EnemyVaristor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 playerMat;
	Vector3 mPosition;
	EnemyAttack enemyAttack;
	float time;
	float  InitialVelocity;
	float vertexTime;
};
#endif