#include "Enemy.h"
#include "Collision.h"
#include "../world/IWorld.h"

Enemy::Enemy(IWorld& world) :Actor(world){
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
void Enemy::OnCollide(Actor& other, CollisionParameter colpara){

}