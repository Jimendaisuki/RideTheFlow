#ifndef ENEMY_VARISTOR_BULLET_H_
#define ENEMY_VARISTOR_BULLET_H_

#include "Actor.h"
#include <memory>

class EnemyBullet :public Actor, public std::enable_shared_from_this<EnemyBullet>
{
public:
	EnemyBullet(IWorld& world, Vector3 position);
	~EnemyBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 mScale;
	float time;
	float speed;
	Vector3 distance;
	Vector3 mRandomTarget;
	Vector3 coppyPosition;
};
#endif