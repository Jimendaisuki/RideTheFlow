#include "MonhanCameraActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"
#include <string>
#include "../math/Math.h"
#include "Player.h"
const Vector3 cameraUpMove = Vector3(0, 30, 0);
const float rotateSpeed = 250.0f;

MonhanCameraActor::MonhanCameraActor(IWorld& world) :Actor(world),
restPosition(Vector3::Zero),
stiffness(3.0f),
friction(0.1f),
mass(2.0f),
velocity(Vector3::Zero)
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	rotateUp = 0;
	rotateLeft = 0;
	position = Vector3(0, 0, 1) * 250.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;
	restPosition = position;
}
MonhanCameraActor::~MonhanCameraActor()
{

}
void MonhanCameraActor::Update()
{
	TackleParameter tp;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		rotateLeft += rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		rotateLeft -= rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		rotateUp += rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		rotateUp -= rotateSpeed * Time::DeltaTime;

	rotateLeft = Math::Clamp(rotateLeft, -70.0f, 70.0f);
	restPosition = Vector3(0, 0, 1) * 250.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;

	Vector3 stretch = (position - restPosition);
	Vector3 force = -stiffness * stretch;
	Vector3 acceleration = force / mass;
	velocity = friction * (velocity + acceleration);
	position += velocity;
	parameter.mat =
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(playerMat.GetPosition());
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().Update();
}
void MonhanCameraActor::Draw() const
{
	DrawFormatString(0, 128, GetColor(0, 0, 0), "playerPosition   %f %f %f", playerMat.GetPosition().x, playerMat.GetPosition().y, playerMat.GetPosition().z);
	DrawFormatString(0, 192, GetColor(0, 0, 0), "cameraPosition   %f %f %f", restPosition.x, restPosition.y, restPosition.z);
	DrawFormatString(0, 256, GetColor(0, 0, 0), "Angle   %f", atan2(playerMat.GetPosition().x - restPosition.x, playerMat.GetPosition().z - restPosition.z) * 180 / 3.1415f + 180);
	DrawFormatString(0, 356, GetColor(0, 0, 0), "rotateUp   %f", rotateUp);
}
void MonhanCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}