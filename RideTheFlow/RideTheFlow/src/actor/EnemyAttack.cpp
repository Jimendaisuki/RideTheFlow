#include "EnemyAttack.h"
#include <math.h>

Vector3 EnemyAttack::AttackVertex(const Vector3& pos, const Vector3 &goPosition, const Vector3& currentPosition, const float& time)
{
	//Žg‚¦‚È‚¢‚Å‚·
	//Vector3 result = pos;
	//	float InitialVelocity = sqrt(2 * 9.8f*currentPosition.y - goPosition.y);
	//	float vertexTime = InitialVelocity / 9.8f;
	//	result.x += (currentPosition.x-goPosition.x ) / vertexTime/60.0f;
	//	result.z += (currentPosition.z-goPosition.z ) / vertexTime/60.0f ;
	//	result = Vector3(result.x, (float)(InitialVelocity*time - 9.8f / 2 * pow(time, 2)), result.z);
	return 0;
}
