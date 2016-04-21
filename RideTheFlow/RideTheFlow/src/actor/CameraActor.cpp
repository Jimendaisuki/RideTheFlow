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
position(0.0f, 0.0f, -200.0f),
target(Matrix4::Identity)
{
	parameter.isDead = false;

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().SetViewAngle(90.0f);
}
CameraActor::~CameraActor()
{
	
}
void CameraActor::Update()
{
	Camera::GetInstance().Position.Set(position);

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