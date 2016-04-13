#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"

Player::Player(IWorld& world):Actor(world){
	parameter.isDead = false;
}
Player::~Player(){

}
void Player::Update() {
}
void Player::Draw() const{
	Model::GetInstance().Draw("X-G1", Vector3::Zero);
}
void Player::OnCollide(Actor& other, CollisionParameter colpara){

}