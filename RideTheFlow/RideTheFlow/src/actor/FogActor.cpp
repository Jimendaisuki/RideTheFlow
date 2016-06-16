#include "FogActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../game/Random.h"
#include "../camera/Camera.h"
#include "../time/Time.h"
#include "../math/Math.h"

FogActor::FogActor(IWorld& world) :
Actor(world),
position(Vector3::Zero),
fogTotalPower(0.0f)
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::FOG_ACTOR;
	SetFogEnable(TRUE);
}
FogActor::~FogActor()
{

}

float angle;

void FogActor::Update()
{
	position = Camera::GetInstance().Position.Get();
	//���_����̋���
	float length = position.Length();
	//�J�����̑O����
	Vector3 front = Vector3::Normalize(Camera::GetInstance().Target.Get() - Camera::GetInstance().Position.Get());
	//���_�֌���������
	Vector3 toOrigin = Vector3::Normalize(-position);
	//�O�ƌ��_�����̂Ȃ��p
	angle = Vector3::Inner(front, toOrigin);
	
	Vector3 cross = Vector3::Cross(front, toOrigin);
	float dot = Vector3::Dot(Camera::GetInstance().Up.Get(), cross);


	Math::Clamp(length, 1.0f, 2000.0f);
	Math::Clamp(angle, 1.0f, 180.0f);
	float fogPower = length * angle;
	float fogMaxPower = 2000.0f * 180.0f * 500.0f;

	fogTotalPower = fogMaxPower / fogPower;

	SetFogStartEnd(0.0f, fogTotalPower);
}
void FogActor::Draw() const
{
	DrawFormatString(900, 10, Vector3::Black.ToColor(), "fogTotalPower : %f", fogTotalPower);
}
void FogActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}