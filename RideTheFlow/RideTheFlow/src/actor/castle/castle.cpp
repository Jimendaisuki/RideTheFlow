#include "castle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"

Castle::Castle(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :
Actor(world)
{
	parameter.isDead = false;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);

	parameter.radius = 10.0f;
}

Castle::~Castle()
{

}

void Castle::Update()
{
	isHit = false;
}

void Castle::Draw() const
{	
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MODEL, parameter.mat);
	
	
	//DrawCube3D(
	//	Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) / 2, 
	//	Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) / 2, 
	//	color, 
	//	GetColor(0, 0, 0), 
	//	false);
	DrawFormatString(10, 100, GetColor(255, 255, 255), "CastlePos	: %f %f %f", Matrix4::GetPosition(parameter.mat).x, Matrix4::GetPosition(parameter.mat).y, Matrix4::GetPosition(parameter.mat).z);
	if (isHit)
	{
		DrawFormatString(10, 120, GetColor(255, 255, 255), "Hit");
	}
}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{
	//parameter.isDead = true;
	isHit = true;
}