#include "Enemy.h"
#include "Collision.h"
#include "../world/IWorld.h"

Enemy::Enemy(IWorld& world) :Actor(world),
playerMat(Matrix4::Identity){
	tex = LoadGraph("res/images.jpg");
	parameter.isDead = false;

	parameter.radius = 1.0f;

	parameter.mat =
		Matrix4::Scale(Vector3(1, 1, 1)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(Vector3(0,0,0));
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