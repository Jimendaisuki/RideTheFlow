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
	ACTIVITYTIME = 5.0f;
	GRAVITY = 1.0f;
	velocity = Vector3::Zero;
	speed = 1;

	parameter.isDead = false;
	parameter.height = 30.0f;
	parameter.radius = 10;
	parameter.mat =
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
	//ACTIVITYTIME -= Time::DeltaTime;
	if (ACTIVITYTIME <= 0)
	{
		parameter.isDead = true;
		return;
	}
	isHit = false;

	//position += velocity;// * Time::DeltaTime;
	//rotate.y += 1000 * Time::DeltaTime;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
		position.x -= 140.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
		position.x += 140.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
		position.y += 140.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
		position.y -= 140.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Q))
		position.z += 140.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::E))
		position.z -= 140.0f * Time::DeltaTime;

	//velocity.y -= GRAVITY * Time::DeltaTime;
	position += velocity * speed;


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

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR, COL_ID::TORNADO_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR, COL_ID::TORNADO_STAGE_COL);
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::SPHERE_SPHERE_COL);

	speed = 1.0f;
}

void Tornado::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::BOX_MODEL, parameter.mat.GetPosition(), Vector3::Zero, Vector3(5));

	Vector3 TopPos, BottomPos;
	BottomPos = Matrix4::GetPosition(parameter.mat);
	TopPos = BottomPos + Vector3(0.0f, parameter.height, 0.0f);



	//DrawCapsule3D(TopPos, BottomPos	, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

	DrawFormatString(10, 70, GetColor(255, 255, 255), "TopPoint	  : %f %f %f", TopPos.x, TopPos.y, TopPos.z);
	DrawFormatString(10, 90, GetColor(255, 255, 255), "BottomPoint: %f %f %f", BottomPos.x, BottomPos.y, BottomPos.z);
	DrawFormatString(10, 110, GetColor(255, 255, 255), "TornadoSize: %f %f %f", Matrix4::GetScale(parameter.mat).x, Matrix4::GetScale(parameter.mat).y, Matrix4::GetScale(parameter.mat).z);
 	DrawFormatString(10, 130, GetColor(255, 255, 255), "isHit		: %d", isHit);
}

void Tornado::OnCollide(Actor& other, CollisionParameter colpara)
{
	switch (colpara.colID){
	case COL_ID::TORNADO_STAGE_COL:
		position = colpara.colPos;
		velocity.y = 0;
		break;
	case COL_ID::TORNADO_CASTLE_COL:
		speed *= 0.75f;
		isHit = true;
		break;
	case COL_ID::TORNADO_ISLAND:
		speed *= 0.75;
		isHit = true;
		break;
	default:
		break;
	}
}