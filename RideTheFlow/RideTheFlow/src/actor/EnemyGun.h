#ifndef ENEMY_GUN_H_
#define ENEMY_GUN_H_

#include"Actor.h"
class EnemyGun :public Actor
{
public:
	EnemyGun(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale);
	~EnemyGun();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 playerMat;
	float coolTime;
	float time;
	bool attack;
	Vector3 mPosition;
};

#endif