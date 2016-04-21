#include "CameraActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"
#include <string>

CameraActor::CameraActor(IWorld& world) :
Actor(world),
position(0.0f, 200.0f, -30.0f),
target(Matrix4::Identity)
{
	parameter.isDead = false;

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);
}
CameraActor::~CameraActor()
{
	
}
void CameraActor::Update()
{
	Vector3 target;
	world.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
		target = other.GetParameter().mat.GetPosition();
	});

	Camera::GetInstance().Target.Set(target);
	Camera::GetInstance().Update();
}
void CameraActor::Draw() const
{	
	//TextDraw::GetInstance().Draw(Point::Zero, target.GetPosition());
	//TextDraw::GetInstance().Draw(Point(0,16), target.GetScale());
}
void CameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}