#include "Tornado.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "TornadeBillboard.h"
#include "../castle/CastleBlock.h"

#include "../../input/Keyboard.h"

const float TornadoDefaltSpeed = 300.0f;
Tornado::Tornado(IWorld& world, Vector3 position_, Vector2 scale_, Vector3 velocity_) :
Actor(world),
position(position_),
velocity(velocity_),
timer(0.0f)
{
	ACTIVITYTIME = 20.0f;
	GRAVITY = 3.0f;
	//velocity = Vector3::Zero;
	speed = 300.0f;

	parameter.isDead = false;
	parameter.height = Vector3(0.0f,300.0f,0.0f);
	parameter.radius = 80;
	parameter.mat =
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	parameter.id = ACTOR_ID::TORNADO_ACTOR;
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

	velocity.y = -GRAVITY;
	position += velocity * speed  * Time::DeltaTime;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);


	//====竜巻の煙生成====//
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
	TopPos = BottomPos + velocity * 1000.0f;

	//デバックコード消しました
	//DrawCapsule3D(TopPos, BottomPos	, 32, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

	DrawFormatString(10, 70, GetColor(255, 255, 255), "TopPoint	  : %f %f %f", TopPos.x, TopPos.y, TopPos.z);
	DrawFormatString(10, 90, GetColor(255, 255, 255), "BottomPoint: %f %f %f", BottomPos.x, BottomPos.y, BottomPos.z);
 	DrawFormatString(10, 130, GetColor(255, 255, 255), "isHit		: %d", isHit);
}

void Tornado::OnCollide(Actor& other, CollisionParameter colpara)
{
	switch (colpara.colID){
	case COL_ID::TORNADO_STAGE_COL:
		// ステージと衝突
		position = colpara.colPos;
		velocity.y = 0;
		break;
	case COL_ID::TORNADO_CASTLE_COL:
		// 城と衝突
		if (speed > 300.0f * 0.5f)
		speed *= 0.5f;
		isHit = true;

		//がれきを飛ばす
		for (int i = 0; i < 20; i++){
			world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<CastleBlock>(world, parameter.mat.GetPosition()));
		}

		break;
	case COL_ID::TORNADO_ISLAND_COL:
		// 浮島と衝突
		if (speed > 300.0f * 0.5f)
		speed *= 0.5f;
		velocity.y = 0;
		//position = colpara.colPos;
		isHit = true;
		break;
	case COL_ID::SPHERE_SPHERE_COL:
		// 
		velocity = colpara.colVelosity;
	case COL_ID::PLAYER_TORNADO_COL:
		velocity = Vector3(colpara.colVelosity.x, 0.0f, colpara.colVelosity.z).Normalized();
	default:
		break;
	}
}