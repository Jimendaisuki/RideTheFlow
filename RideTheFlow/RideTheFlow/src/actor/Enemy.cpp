#include "Enemy.h"

Enemy::Enemy(){
	tex = LoadGraph("res/images.jpg");
	parameter.isDead = false;
}
Enemy::~Enemy(){

}
void Enemy::Update() {
}
void Enemy::Draw() const{
	DrawGraph(0, 0, tex, TRUE);
}
void Enemy::OnCollide(Actor& other){

}