#include "Tornado.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"

#include "../../input/Keyboard.h"

Tornado::Tornado(IWorld& world, Vector3 position_, Vector2 scale_, Vector3 velocity_) :
Actor(world),
position(position_),
velocity(velocity_)
{
	parameter.radius = scale_.x;
	scale = Vector3(parameter.radius, scale_.y, parameter.radius);

	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
}

Tornado::~Tornado()
{

}

void Tornado::Update()
{
	isHit = false;

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR, COL_ID::CAPSULE_AABB_COL);

	//position += velocity;// * Time::DeltaTime;
	rotate.y += 1000 * Time::DeltaTime;

	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::SPHERE_SPHERE_COL);
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
		position.x -= 440.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
		position.x += 440.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
		position.y += 440.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
		position.y -= 440.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Q))
		position.z += 440.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::E))
		position.z -= 440.0f * Time::DeltaTime;

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
	//Model::GetInstance().Draw(MODEL_ID::TORNADO_MODEL, parameter.mat);

	//Vector3 TopPos = Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	//Vector3 BottomPos = Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
	Vector3 startPos	= Matrix4::GetPosition(parameter.mat);
	Vector3 endPos		= Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3::Up;

	DrawLine3D(startPos, endPos, GetColor(255, 255, 255));
	DrawCapsule3D(startPos, endPos	, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	DrawFormatString(10, 40, GetColor(255, 255, 255), "TopPoint	  : %f %f %f", startPos.x, startPos.y, startPos.z);
	DrawFormatString(10, 60, GetColor(255, 255, 255), "BottomPoint: %f %f %f", endPos.x, endPos.y, endPos.z);
	DrawFormatString(10, 80, GetColor(255, 255, 255), "TornadoSize: %f %f %f", Matrix4::GetScale(parameter.mat).x, Matrix4::GetScale(parameter.mat).y, Matrix4::GetScale(parameter.mat).z);
 	DrawFormatString(10, 100, GetColor(255, 255, 255), "isHit		: %d", isHit);
}

void Tornado::OnCollide(Actor& other, CollisionParameter colpara)
{
	isHit = true;
}