#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../time/Time.h"

Player::Player(IWorld& world):
Actor(world),
position(Vector3::Zero)
{
	parameter.isDead = false;
	parameter.radius = 10.0f;

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

	parameter.mat =
		Matrix4::Scale(Vector3(1, 1, 1)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
}
void Player::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
	DrawSphere3D(parameter.mat.GetPosition(), parameter.radius, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{
	position = Vector3(0, 0, 0);
}