#include "castle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"

Castle::Castle(IWorld& world, Vector3 position, Vector3 scale) :
Actor(world)
{
	parameter.isDead = false;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	parameter.radius = 10.0f;
}

Castle::~Castle()
{

}

void Castle::Update()
{
	color = GetColor(255, 255, 255);
}

void Castle::Draw() const
{
	// プレイヤー描画情報を流用
	//Model::GetInstance().Draw(MODEL_ID::TORNADO_MODEL, position);

	DrawCube3D(
		Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) / 2, 
		Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) / 2, 
		color, 
		GetColor(0, 0, 0), 0);
}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{
	//parameter.isDead = true;

	color = GetColor(255, 255, 0);
}