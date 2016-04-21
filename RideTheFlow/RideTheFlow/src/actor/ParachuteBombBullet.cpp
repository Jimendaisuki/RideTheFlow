#include "ParachuteBombBullet.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include"../time/Time.h"

ParachuteBombBullet::ParachuteBombBullet(IWorld& world, Vector3 position, float height) :Actor(world),
mHeight(height+position.y),
time(0),
HeightJuge(false),
mPosition(position)
{
	parameter.isDead = false;
}
ParachuteBombBullet::~ParachuteBombBullet(){

}
void ParachuteBombBullet::Update() {
	time += Time::DeltaTime*5.0f;
	if (velocity.y >= 0)
	{
		initialVelocity = sqrt(mHeight*(2 * 9.8f));
		mPosition.y = initialVelocity*time - 1.0f / 2.0f*9.8f*pow(time, 2);
		velocity.y = initialVelocity - (9.8 * time);
	}
	else
	{
		mPosition.y -= 2.5f*Time::DeltaTime;
	}
	parameter.mat = Matrix4::Translate(mPosition);
}
void ParachuteBombBullet::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}
void ParachuteBombBullet::OnCollide(Actor& other, CollisionParameter colpara){

}