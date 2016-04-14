#include "CameraActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"

CameraActor::CameraActor(IWorld& world) :
Actor(world),
position(0.0f, 0.0f, -100.0f)
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
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		position.x -= 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		position.x += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		position.z += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		position.z -= 100.0f * Time::DeltaTime;
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Update();
}
void CameraActor::Draw() const
{	
	TextDraw::GetInstance().Draw(position);
}
void CameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}