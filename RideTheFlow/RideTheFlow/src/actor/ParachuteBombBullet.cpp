#include "ParachuteBombBullet.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include"../time/Time.h"

ParachuteBombBullet::ParachuteBombBullet(IWorld& world, Vector3 position) :Actor(world),
time(0),
HeightJuge(false),
mPosition(position),
coppyPosition(position)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
}
ParachuteBombBullet::~ParachuteBombBullet(){

}
void ParachuteBombBullet::Update() {
	time += Time::DeltaTime*5.0f;
	if (velocity.y >= 0)
	{
		float initialVelocity = sqrt(mHeight*(2 * 9.8f));
		mPosition.y = initialVelocity*time - 1.0f / 2.0f*9.8f*pow(time, 2);
		velocity.y = initialVelocity - (9.8 * time);
	}
	else
	{
		mPosition.y -= 0.1f*Time::DeltaTime*60.0f;
	}
	parameter.mat = Matrix4::Translate(mPosition+Vector3(0.0f,coppyPosition.y,0.0f));
}
void ParachuteBombBullet::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat);
}
void ParachuteBombBullet::OnCollide(Actor& other, CollisionParameter colpara){

}