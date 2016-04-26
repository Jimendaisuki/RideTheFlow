#include "Enemy.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../actor/EnemyBullet.h"
#include "../time/Time.h"
#include "../graphic/Model.h"
Enemy::Enemy(IWorld& world,Vector3 position) :Actor(world),
playerMat(Matrix4::Identity),
coolTime(1.0f),
time(0.0f),
attack(true),
mPosition(position){
	tex = LoadGraph("res/images.jpg");
	parameter.isDead = false;

	parameter.radius = 1.0f;

	parameter.mat =
		Matrix4::Scale(Vector3(1, 1, 1)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) ;


}
Enemy::~Enemy(){

}
void Enemy::Update() {
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	if (Vector3::Distance(playerMat.GetPosition(), mPosition) <= 40.0f&&attack)
	{
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, 30.0f));
		time = 0;
		attack = false;
	}
	else
	{
		time += Time::DeltaTime;
		if (time >= coolTime)
			attack = true;
	}
}
void Enemy::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, mPosition);
}
void Enemy::OnCollide(Actor& other, CollisionParameter colpara){

}