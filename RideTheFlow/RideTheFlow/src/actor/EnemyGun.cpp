#include"EnemyGun.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../time/Time.h"
#include "../graphic/Model.h"
#include "EnemyGunBullet.h"
EnemyGun::EnemyGun(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :Actor(world),
coolTime(1.0f),
time(0.0f),
attack(true),
mPosition(position){
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
}
EnemyGun::~EnemyGun(){

}
void EnemyGun::Update() {
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	if (Vector3::Distance(playerMat.GetPosition(), mPosition) <= 40.0f&&attack)
	{
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyGunBullet>(world, mPosition, Vector3(0), Vector3(5),3.0f));
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
void EnemyGun::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, mPosition);
}
void EnemyGun::OnCollide(Actor& other, CollisionParameter colpara){

}