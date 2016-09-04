#include "HomeActor.h"
#include "../../world/IWorld.h"
#include "../Collision.h"
#include "../../graphic/Model.h"
#include "../particle/BreakCastle.h"
#include "../../sound/Sound.h"

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
	Model::GetInstance().Draw(MODEL_ID::HOME_MODEL, parameter.mat, 1.0f);
}
void HomeActor::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
	Sound::GetInstance().PlaySE(SE_ID::CASTLE_BREAK_SE);

	if (colpara.colID == COL_ID::WIND_HOME_COL)
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, parameter.mat.GetPosition(), CASTLE_SELECT::HOME, BREAK_SELECT::WIND_FLOW));
	else if (colpara.colID == COL_ID::TORNADO_CASTLE_COL)
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, parameter.mat.GetPosition(), CASTLE_SELECT::HOME, BREAK_SELECT::TORNADO));
}