#include "FloatingIsland.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../NoShipArea.h"

FroatingIsland::FroatingIsland(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :
Actor(world)
{
	HP = 50;

	parameter.isDead = false;
	parameter.radius = 120;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	//ëDÇ™ì¸ÇÁÇ»Ç¢ÇÊÇ§Ç…ê›íË
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world, 
		parameter.mat.GetPosition()+Vector3(0.0f,0.0f,0.0f),
		parameter.radius, *this));
}

FroatingIsland::~FroatingIsland()
{

}

void FroatingIsland::Update()
{
	//if (HP <= 0) parameter.isDead = true;

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR , COL_ID::SPHERE_CAPSULE);
}

void FroatingIsland::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::ISLE_1_MODEL, parameter.mat);
}

void FroatingIsland::OnCollide(Actor& other, CollisionParameter colpara)
{
	HP--;
	parameter.mat =
		Matrix4::Translate(colpara.colPos);
}