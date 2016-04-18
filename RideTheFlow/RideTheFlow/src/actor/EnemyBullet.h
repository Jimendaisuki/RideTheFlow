#ifndef ENEMY_BULLET_H_
#define ENEMY_BULLET_H_

#include "Actor.h"
#include "EnemyAttack.h"
class EnemyBullet :public Actor
{
public:
	EnemyBullet(IWorld& world);
	~EnemyBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 playerMat;
	EnemyAttack enemyAttack;
	float time;
	float  InitialVelocity;
	float vertexTime;
	Vector3 mPosition;

};

#endif;