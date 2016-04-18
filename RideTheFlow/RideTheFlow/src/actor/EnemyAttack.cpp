#include "EnemyAttack.h"
#include <math.h>

EnemyAttack::EnemyAttack() :
time(0),
InitialVelocity(0),
mPosition(0.0f,0.0f,0.0f),
vertexTime(0)
{

}
Vector3 EnemyAttack::AttackVertex(const Vector3 &goPosition, const Vector3 &vertex)
{
	time += Time::DeltaTime / 60.0f;
	InitialVelocity = sqrt(2 * 9.8f*vertex.y - goPosition.y);
	vertexTime = InitialVelocity / 9.8f;
	mPosition += vertex - goPosition / vertexTime / 60.0f;
	return Vector3(mPosition.x, (float)(InitialVelocity*time - 9.8f / 2 * pow(time, 2)), mPosition.z);
}
