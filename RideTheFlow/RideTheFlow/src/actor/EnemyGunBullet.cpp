#include "EnemyGunBullet.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"

EnemyGunBullet::EnemyGunBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, float speed) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(position),
mSpeed(speed)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	parameter.radius = 5.0f;
	mDirection = Vector3::Direction(mPosition, playerMat.GetPosition()).Normalized()*speed;
}
EnemyGunBullet::~EnemyGunBullet()
{

}
void EnemyGunBullet::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::SPHERE_SPHERE_COL);
	mPosition += mDirection*Time::DeltaTime*60.0f;
	parameter.mat = Matrix4::Translate(mPosition);
}

void EnemyGunBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyGunBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}