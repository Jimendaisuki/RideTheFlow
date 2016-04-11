#include "Player.h"

Player::Player(){
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
void Player::OnCollide(Actor& other){

}