#include "ParachuteBombBullet.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include"../time/Time.h"

ParachuteBombBullet::ParachuteBombBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, float height) :Actor(world),
mHeight(height-position.y),
time(0),
HeightJuge(false),
mPosition(position),
coppyPosition(position)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
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
		mPosition.y -= 0.1f*Time::DeltaTime*60.0f;
	}
	parameter.mat = Matrix4::Translate(mPosition+Vector3(0.0f,coppyPosition.y,0.0f));
}
void ParachuteBombBullet::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat);
}
void ParachuteBombBullet::OnCollide(Actor& other, CollisionParameter colpara){

}