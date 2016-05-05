#ifndef ENEMY_BULLET_H_
#define ENEMY_BULLET_H_

#include "Actor.h"
class EnemyBullet :public Actor
{
public:
	EnemyBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, float initialVelocity);
	~EnemyBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 playerMat;
	float time;
	float  mInitialVelocity;
	float angle;
	float speed;
	Vector3 mPosition;
	Vector3 coppyPosition;
	Vector3 mDirection;
};

#endif;