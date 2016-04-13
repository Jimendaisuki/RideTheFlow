#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../math/Vector3.h"

Player::Player(IWorld& world):Actor(world){
	tex = LoadGraph("res/body.jpg");
	parameter.isDead = false;
}
Player::~Player(){

}
void Player::Update() {
}
void Player::Draw() const{
	DrawGraph(0, 0, tex, TRUE);
}
void Player::OnCollide(Actor& other, CollisionParameter colpara){

}