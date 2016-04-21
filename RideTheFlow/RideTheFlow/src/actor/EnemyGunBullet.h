#ifndef ENEMY_GUN_BULLET_H_
#define ENEMY_GUN_BULLET_H_

#include "Actor.h"
#include "EnemyAttack.h"
class EnemyGunBullet :public Actor
{
public:
	EnemyGunBullet(IWorld& world, Vector3 position);
	~EnemyGunBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 mDirection;

};

#endif