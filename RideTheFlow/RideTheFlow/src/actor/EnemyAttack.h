#ifndef ENEMY_ATTACK_H_
#define ENEMY_ATTACK_H_

#include "../math/Vector3.h"
#include "../time/Time.h"
class EnemyAttack
{
public:
	//�w�肵�����_��ʂ�O��
	static Vector3 AttackVertex(const Vector3& pos,const Vector3 &goPosition, const Vector3& currentPosition, const float& time);
	static Vector3 AttackEndPoint(const Vector3 &goPosition, const Vector3 &endPoaisiton);
};

#endif