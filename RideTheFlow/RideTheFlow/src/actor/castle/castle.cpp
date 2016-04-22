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

	Vector2 side = Vector2(scale.x, scale.z) / 2;
	parameter.radius = sqrtf(side.x * side.x + side.y + side.y);
}

Castle::~Castle()
{

}

void Castle::Update()
{

}

void Castle::Draw() const
{	
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MODEL, parameter.mat);
	
	Vector3 startPos, endPos;
	startPos = Matrix4::GetPosition(parameter.mat);
	endPos = Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3::Up;
	DrawCapsule3D(startPos, endPos, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
	
	//DrawLine3D(startPos, endPos, GetColor(255, 0, 0));

	//DrawCube3D(
	//	Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) / 2, 
	//	Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) / 2, 
	//	color, 
	//	GetColor(0, 0, 0), 
	//	false);
	//DrawFormatString(10, 100, GetColor(255, 255, 255), "CastlePos	: %f %f %f", Matrix4::GetPosition(parameter.mat).x, Matrix4::GetPosition(parameter.mat).y, Matrix4::GetPosition(parameter.mat).z);
	//DrawFormatString(10, 120, GetColor(255, 255, 255), "CastleScale	: %f %f %f", Matrix4::GetScale(parameter.mat).x, Matrix4::GetScale(parameter.mat).y, Matrix4::GetScale(parameter.mat).z);
	//if (isHit)
	//{
	//	DrawFormatString(10, 400, GetColor(255, 255, 255), "Hit");
	//}
}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{
	//parameter.isDead = true;
}