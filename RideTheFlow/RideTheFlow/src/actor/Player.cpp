#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../camera/Camera.h"
#include "../time/Time.h"

Player::Player(IWorld& world):
Actor(world),
position(Vector3::Zero),
cameraPos(0.0f, 0.0f, -100.0f)
{
	parameter.isDead = false;
	parameter.radius = 10.0f;
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);

	parameter.mat =
		Matrix4::Scale(Vector3(1,1,1)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
}
Player::~Player(){

}
void Player::Update() 
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::SPHERE_SPHERE_COL);
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		position.x -= 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		position.x += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		position.z += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		position.z -= 100.0f * Time::DeltaTime;

	Camera::GetInstance().Position.Set(cameraPos);

	parameter.mat =
		Matrix4::Scale(Vector3(1, 1, 1)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
}
void Player::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL,Matrix4::GetPosition(parameter.mat));
	DrawSphere3D(Matrix4::GetPosition(parameter.mat), parameter.radius, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{
	position = Vector3(0, 0, 0);
}