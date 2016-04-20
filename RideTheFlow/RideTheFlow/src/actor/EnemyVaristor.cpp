#include "EnemyVaristor.h"

#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include "../time/Time.h"
EnemyVaristor::EnemyVaristor(IWorld& world) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(parameter.mat.GetPosition()),
time(0),
InitialVelocity(0.0f),
vertexTime(0)
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
}
EnemyVaristor::~EnemyVaristor()
{

}
void EnemyVaristor::Update()
{
	time += Time::DeltaTime;
	parameter.mat = Matrix4::Translate(EnemyAttack::AttackVertex(parameter.mat.GetPosition(), parameter.mat.GetPosition(), playerMat.GetPosition(), time));
}

void EnemyVaristor::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyVaristor::OnCollide(Actor& other, CollisionParameter colpara)
{

}