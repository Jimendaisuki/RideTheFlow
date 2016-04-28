#ifndef ENEMY_GUN_BULLET_H_
#define ENEMY_GUN_BULLET_H_

#include "Actor.h"
#include "EnemyAttack.h"
#include <memory>
class EnemyGunBullet :public Actor, public std::enable_shared_from_this<EnemyGunBullet>
{
public:
	EnemyGunBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale,Vector3 randomTarget,float speed);
	~EnemyGunBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 playerMat;
	Vector3 mPosition;
	Vector3 mDirection;
	float mSpeed;

};

#endif