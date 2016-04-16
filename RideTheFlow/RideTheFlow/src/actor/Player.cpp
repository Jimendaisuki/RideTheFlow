#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../camera/Camera.h"
#include "../graphic/Anime.h"
#include "../time/Time.h"

Player::Player(IWorld& world):
Actor(world),
position(Vector3::Zero),
animetime(0.0f)
{
	parameter.isDead = false;
}
Player::~Player(){

}
void Player::Update() 
{
	animetime += Time::DeltaTime;
}
void Player::Draw() const
{
	Anime::GetInstance().AttachAnime(MODEL_ID::TEST_MODEL, 0);
	Anime::GetInstance().PlayAnime(MODEL_ID::TEST_MODEL, 0, animetime*100.0f);
	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, Vector3::Zero);

	//Sprite::GetInstance().Draw(SPRITE_ID::PLAYER_SPRITE, Vector2(-150, -150), 0.2f);
}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{

}