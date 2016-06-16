#include "FloatingIsland.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"


FroatingIsland::FroatingIsland(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :
Actor(world)
{
	HP = 50;

	parameter.isDead = false;
	parameter.radius = 200;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
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
	DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), parameter.radius, 20, 1, 1, FALSE);
}

void FroatingIsland::OnCollide(Actor& other, CollisionParameter colpara)
{
	HP--;
	parameter.mat =
		Matrix4::Translate(colpara.colPos);
}