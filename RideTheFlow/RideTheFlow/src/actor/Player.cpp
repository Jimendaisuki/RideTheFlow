#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../camera/Camera.h"

Player::Player(IWorld& world):
Actor(world),
position(Vector3::Zero),
cameraPos(0.0f, 0.0f, -100.0f)
{
	parameter.isDead = false;

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);
}
Player::~Player(){

}
void Player::Update() 
{
	Camera::GetInstance().Position.Set(cameraPos);
}
void Player::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, Vector3::Zero);
	Sprite::GetInstance().Draw(SPRITE_ID::PLAYER_SPRITE, Vector2(-150, -150), 0.2f);
}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{

}