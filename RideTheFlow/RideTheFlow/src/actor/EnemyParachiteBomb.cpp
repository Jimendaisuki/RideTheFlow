#include "Collision.h"
#include "EnemyParachuteBomb.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include"../time/Time.h"
#include"ParachuteBombBullet.h"
EnemyParachiteBomb::EnemyParachiteBomb(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :Actor(world),
coolTime(10.0f),
time(0.0f),
attack(true),
mPosition(position)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
}
EnemyParachiteBomb::~EnemyParachiteBomb(){

}
void EnemyParachiteBomb::Update() {
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	if (Vector3::Distance(playerMat.GetPosition(), mPosition) <= 40.0f&&attack)
	{
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<ParachuteBombBullet>(world, mPosition, Vector3(0, 0, 0), Vector3(5, 5, 5), playerMat.GetPosition().y + 5.0f));
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
void EnemyParachiteBomb::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}
void EnemyParachiteBomb::OnCollide(Actor& other, CollisionParameter colpara){

}