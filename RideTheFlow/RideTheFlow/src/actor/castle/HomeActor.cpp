#include "HomeActor.h"
#include "../../world/IWorld.h"
#include "../Collision.h"
#include "../../graphic/Model.h"

HomeActor::HomeActor(IWorld& world, float scale, const Vector3& position_, const Vector3& rotate_) :
Actor(world)
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::CASTLE_ACTOR;
	parameter.radius = 100.0f;
	parameter.mat = 
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate_.z) *
		Matrix4::RotateX(rotate_.x) *
		Matrix4::RotateY(rotate_.y) *
		Matrix4::Translate(position_);
}
HomeActor::~HomeActor()
{

}

void HomeActor::Update()
{

}
void HomeActor::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::HOME_MODEL, parameter.mat);
}
void HomeActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}