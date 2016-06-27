#include "AirGun.h"
#include "Collision.h"
#include "../time/Time.h"
#include "../graphic/Model.h"
#include "../math/Quaternion.h"
#include "../sound/Sound.h"

AirGun::AirGun(IWorld& world, Vector3 position_, Vector3 velocity_) :
Actor(world),
position(position_),
velocity(Vector3::Normalize(velocity_)),
range(0.0f){
	for (int i = 0; i < 3; i++)
	{
		rotates.push_back(Matrix4::Identity);
		mats.push_back(Matrix4::Identity);
	}
	rotates.at(0) *= Quaternion::RotateAxis(Vector3(0, 1, 0), 30.0f);
	rotates.at(1) *= Quaternion::RotateAxis(Vector3(0, 0, 1).Normalized(), -45.0f);
	rotates.at(2) *= Quaternion::RotateAxis(Vector3(1, 0, 0), 90.0f);

	parameter.isDead = false;
	parameter.radius = 200.0f;

	Sound::GetInstance().PlaySE(SE_ID::NORMAL_WIND_SE);
}
AirGun::~AirGun(){

}
void AirGun::Update(){
	range += Vector3::Length(velocity * 1000.0f * Time::DeltaTime);
	position += velocity * 1000.0f * Time::DeltaTime;
	if (range > 1000.0f){
		parameter.isDead = true;
	}

	rotates.at(0) *= Quaternion::RotateAxis(Vector3(0, 1, 0), 30.0f);
	rotates.at(1) *= Quaternion::RotateAxis(Vector3(1, 1, 0).Normalized(), -30.0f);
	rotates.at(2) *= Quaternion::RotateAxis(Vector3(0, 0, 1), 30.0f);
		
	for (int i = 0; i < 3; i++)
	{
		mats.at(i) = 
			Matrix4::Scale(0.05f + i * 0.0f) * 
			rotates.at(i) * 
			Matrix4::Translate(position);
	}

	parameter.mat = mats.at(0);
}
void AirGun::Draw() const{
	for (int i = 0; i < 3; i++)
	{
		Model::GetInstance().Draw(MODEL_ID::AIR_BALL_MODEL, mats.at(i));
	}
	//DrawSphere3D(position, 10.0f, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
	//Model::GetInstance().Draw(MODEL_ID::AIR_BALL_MODEL, position, Vector3::Zero, Vector3(0.05f));
	//Model::GetInstance().Draw(MODEL_ID::AIR_BALL_MODEL, position, Vector3::Zero, Vector3(0.07f));
	//Model::GetInstance().Draw(MODEL_ID::AIR_BALL_MODEL, position, Vector3::Zero, Vector3(0.010f));
}
void AirGun::OnCollide(Actor& other, CollisionParameter colpara){
	if (colpara.colID == COL_ID::CASTLE_AIRGUN_COL)
	{
		parameter.isDead = true;
	}
}