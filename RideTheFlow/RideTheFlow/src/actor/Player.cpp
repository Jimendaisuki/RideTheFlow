#include "Player.h"
#include "../graphic/Sprite.h"

Player::Player(){
	parameter.isDead = false;
}
Player::~Player(){

}
void Player::Update(){

}
void Player::Draw() const{
	Sprite::GetInstance().Draw("images", Vector2(100, 100));
}
void Player::OnCollide(Actor& other){

}