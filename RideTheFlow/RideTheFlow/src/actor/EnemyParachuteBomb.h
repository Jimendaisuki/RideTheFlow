#ifndef ENEMY_PARACHUTE_BOMB_H_
#define ENEMY_PARACHUTE_BOMB_H_
#include "Actor.h"

class EnemyParachiteBomb:public Actor
{
public:
	EnemyParachiteBomb(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale);
	~EnemyParachiteBomb();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Vector3 mPosition;
	Matrix4 playerMat;
	float coolTime;
	float time;
	bool attack;
};

#endif