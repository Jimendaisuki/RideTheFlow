#ifndef ENEMY_VARISTOR_BULLET_H_
#define ENEMY_VARISTOR_BULLET_H_

#include "Actor.h"
#include "EnemyAttack.h"
#include <memory>

class EnemyVaristorBullet :public Actor, public std::enable_shared_from_this<EnemyVaristorBullet>
{
public:
	EnemyVaristorBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale);
	~EnemyVaristorBullet();
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
	float speed;
	Vector3 distance;
};
#endif