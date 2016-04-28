#include "Tornado.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "TornadeBillboard.h"

#include "../../input/Keyboard.h"

Tornado::Tornado(IWorld& world, Vector3 position_, Vector2 scale_, Vector3 velocity_) :
Actor(world),
position(position_),
velocity(velocity_),
timer(0.0f)
{
	ACTIVITYTIME = 5.0f;
	GRAVITY = 1.0f;
	//velocity = Vector3::Zero;
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
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::STAGE_ACTOR, COL_ID::TORNADO_STAGE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR , COL_ID::TORNADO_CASTLE_COL);
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::ISLAND_ACTOR , COL_ID::TORNADO_ISLAND_COL);

	ACTIVITYTIME -= Time::DeltaTime;
	if (ACTIVITYTIME <= 0)
	{
		parameter.isDead = true;
		return;
	}
	isHit = false;

	//position += velocity;// * Time::DeltaTime;
	//rotate.y += 1000 * Time::DeltaTime;

	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
	//	position.x -= 100.0f * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
	//	position.x += 100.0f * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
	//	position.y += 100.0f * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
	//	position.y -= 100.0f * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Q))
	//	position.z += 100.0f * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::E))
	//	position.z -= 100.0f * Time::DeltaTime;

	position += velocity * speed;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	velocity.y -= GRAVITY * Time::DeltaTime;
	speed = 1.0f;

	//====�����̉�����====//
	timer += Time::DeltaTime;
	if (timer > 0.08f){
		timer = 0.0f;
		Vector3 pos = parameter.mat.GetPosition();
		world.Add(ACTOR_ID::SAND_ACTOR, std::make_shared<TornadeBillboard>(world, pos, shared_from_this()));
	}
}

void Tornado::Draw() const
{
	Vector3 TopPos, BottomPos;
	BottomPos = Matrix4::GetPosition(parameter.mat);
	TopPos = BottomPos + Vector3(0.0f, parameter.height, 0.0f);

	DrawCapsule3D(TopPos, BottomPos	, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

	DrawFormatString(10, 70, GetColor(255, 255, 255), "TopPoint	  : %f %f %f", TopPos.x, TopPos.y, TopPos.z);
	DrawFormatString(10, 90, GetColor(255, 255, 255), "BottomPoint: %f %f %f", BottomPos.x, BottomPos.y, BottomPos.z);
 	DrawFormatString(10, 130, GetColor(255, 255, 255), "isHit		: %d", isHit);
}

void Tornado::OnCollide(Actor& other, CollisionParameter colpara)
{
	switch (colpara.colID){
	case COL_ID::TORNADO_STAGE_COL:
		// �X�e�[�W�ƏՓ�
		position = colpara.colPos;
		velocity.y = 0;
		break;
	case COL_ID::TORNADO_CASTLE_COL:
		// ��ƏՓ�
		speed *= 0.5f;
		isHit = true;
		break;
	case COL_ID::TORNADO_ISLAND_COL:
		// �����ƏՓ�
		speed *= 0.5f;
		velocity.y = 0;
		position = colpara.colPos;
		isHit = true;
		break;
	case COL_ID::SPHERE_SPHERE_COL:
		// 
		velocity = colpara.colVelosity;
	default:
		break;
	}
}