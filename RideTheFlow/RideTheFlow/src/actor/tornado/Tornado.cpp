#include "Tornado.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"

#include "../../input/Keyboard.h"

Tornado::Tornado(IWorld& world, Vector3 position, Vector3 velocity) :
Actor(world),
position(position),
velocity(velocity),
scale(Vector3(1.0f, 12.0f, 1.0f))
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

Tornado::~Tornado()
{

}

void Tornado::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR, COL_ID::CYLINDER_BOX_COL);

	//position += velocity;// * Time::DeltaTime;
	rotate.y += 1000;// *Time::DeltaTime;

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::SPHERE_SPHERE_COL);
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
		position.x -= 20.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
		position.x += 20.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
		position.y += 20.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
		position.y -= 20.0f * Time::DeltaTime;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	//scale -= Vector3(0.1f * Time::DeltaTime, 0.0f, 0.1f * Time::DeltaTime);
	//if (scale.x + scale.z <= 0.2f)
	//{
	//	world.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(world, Vector3(0, 0, 0), Vector3(10, 0, 0)));
	//	parameter.isDead = true;
	//}
}

void Tornado::Draw() const
{
	// プレイヤー描画情報を流用
	//Model::GetInstance().Draw(MODEL_ID::TORNADO_MODEL, Matrix4::GetPosition(parameter.mat), rotate, scale);
	//Sprite::GetInstance().Draw(SPRITE_ID::PLAYER_SPRITE, Vector2(-150, -150), 0.5f);


	Vector3 TopPos		= Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	Vector3 BottomPos	= Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);

	DrawLine3D(TopPos, BottomPos, GetColor(255, 255, 255));
	DrawCapsule3D(TopPos, BottomPos, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	DrawFormatString(10, 40, GetColor(255, 255, 255), "TopPoint	  : %f %f %f", TopPos.x, TopPos.y, TopPos.z);
	DrawFormatString(10, 60, GetColor(255, 255, 255), "BottomPoint: %f %f %f", BottomPos.x, BottomPos.y, BottomPos.z);

}

void Tornado::OnCollide(Actor& other, CollisionParameter colpara)
{

}