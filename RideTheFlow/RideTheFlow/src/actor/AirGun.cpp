#include "AirGun.h"
#include "Collision.h"
#include "../time/Time.h"
#include "../graphic/Model.h"

AirGun::AirGun(IWorld& world, Vector3 position_, Vector3 velocity_) :
Actor(world),
position(position_),
velocity(Vector3::Normalize(velocity_)),
range(0.0f){
	parameter.isDead = false;
}
AirGun::~AirGun(){

}
void AirGun::Update(){
	range += Vector3::Length(velocity * 1000.0f * Time::DeltaTime);
	position += velocity * 1000.0f * Time::DeltaTime;
	if (range > 1000.0f){
		parameter.isDead = true;
	}
}
void AirGun::Draw() const{
	//DrawSphere3D(position, 10.0f, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
	Model::GetInstance().Draw(MODEL_ID::AIR_BALL_MODEL, position, Vector3::Zero, Vector3(0.05f));
	Model::GetInstance().Draw(MODEL_ID::AIR_BALL_MODEL, position, Vector3::Zero, Vector3(0.07f));
	Model::GetInstance().Draw(MODEL_ID::AIR_BALL_MODEL, position, Vector3::Zero, Vector3(0.010f));
}
void AirGun::OnCollide(Actor& other, CollisionParameter colpara){

}