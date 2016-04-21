#ifndef ENEMY_VARISTOR_H_
#define ENEMY_VARISTOR_H_
#include "Actor.h"

class EnemyVaristor:public Actor
{
public:
	EnemyVaristor(IWorld& world, Vector3 position);
	~EnemyVaristor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	int tex;
	Matrix4 playerMat;
	float coolTime;
	float time;
	bool attack;
	Vector3 mPosition;
};

#endif