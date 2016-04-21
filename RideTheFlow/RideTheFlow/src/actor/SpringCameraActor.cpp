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
stiffness(0.0f),
friction(0.0f),
mass(1.0f)
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});

}
SpringCameraActor::~SpringCameraActor()
{

}
void SpringCameraActor::Update()
{
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

	point = playerMat.GetFront();
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(point);
	Camera::GetInstance().Update();
}
void SpringCameraActor::Draw() const
{
	//TextDraw::GetInstance().Draw(Point::Zero, target.GetPosition());
	//TextDraw::GetInstance().Draw(Point(0,16), target.GetScale());
}
void SpringCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}