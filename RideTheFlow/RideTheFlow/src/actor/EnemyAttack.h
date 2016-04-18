#ifndef ENEMY_ATTACK_H_
#define ENEMY_ATTACK_H_

#include "../math/Vector3.h"
#include "../time/Time.h"
class EnemyAttack
{
public:
	EnemyAttack();
	//Žw’è‚µ‚½’¸“_‚ð’Ê‚é‹O“¹
	Vector3 AttackVertex(const Vector3 &goPosition, const Vector3 &vertex);
	Vector3 AttackEndPoint(const Vector3 &goPosition, const Vector3 &endPoaisiton);

private:
	float time;
	float vertexTime;
	float InitialVelocity;
	Vector3 mPosition;
};

#endif