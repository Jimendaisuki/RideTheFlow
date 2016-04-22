#include "SpringCameraActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"
#include <string>

SpringCameraActor::SpringCameraActor(IWorld& world) :Actor(world),
velocity(Vector3::Zero),
restPosition(Vector3::Zero),
stiffness(0.2f),
friction(0.5f),
mass(2.0f)

{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	position = playerMat.GetPosition();
	restPosition = position;
}
SpringCameraActor::~SpringCameraActor()
{

}
void SpringCameraActor::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	restPosition = playerMat.GetPosition();
	// �o�l�̐L�ы���v�Z
	Vector3 stretch = (position - restPosition);
	// �o�l�̗͂��v�Z
	Vector3 force = -stiffness * stretch;
	// �����x��ǉ�
	Vector3 acceleration = force / mass;
	// �ړ����x���v�Z
	velocity = friction * (velocity + acceleration);
	// ���W�̍X�V
	position += velocity;

	point = playerMat.GetPosition();
	Camera::GetInstance().Position.Set(position + playerMat.GetFront().Normalized()*150.0f+playerMat.GetUp().Normalized()*40.0f);
	Camera::GetInstance().Target.Set(point);
	Camera::GetInstance().Update();
}
void SpringCameraActor::Draw() const
{
	//TextDraw::GetInstance().Draw(Point(0,16), target.GetScale());
}
void SpringCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}