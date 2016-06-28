#include "Tornado.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../castle/CastleBlock.h"

#include "../../input/Keyboard.h"
#include "../particle/TornadoParticle.h"
#include "../../sound/Sound.h"
#include "../../WindAndTornadoSetting.h"


const float TornadoDefaltSpeed = 1000.0f;
Tornado::Tornado(IWorld& world, Vector3 position_, Vector2 scale_, Vector3 velocity_,float radius_) :
Actor(world),
position(position_.x, -800.0f, position_.z),
velocity(Vector3(velocity_.x,0.0f,velocity_.z).Normalized()),
timer(0.0f),
radius(radius_ * 6.0f)
{
	ACTIVITYTIME = TornadoLifeLimit;
	GRAVITY = 0.0f;
	speed = TornadoSpeed;

	parameter.isDead = false;
	parameter.height = Vector3(0.0f,3000.0f,0.0f);
	parameter.radius = radius;
	parameter.mat =
		Matrix4::Translate(position);

	parameter.id = ACTOR_ID::TORNADO_ACTOR;

	ps_parameter.intervalSec = 0.05f;
	ps_parameter.lifeTimeLimit = 9999.0f;
	ps_parameter.sameEmissiveNum = 2;

	Sound::GetInstance().PlaySE(SE_ID::STORMAKED_SE);
	Sound::GetInstance().PlaySE(SE_ID::STRONGWIND_SE, DX_PLAYTYPE_LOOP);
	Sound::GetInstance().StopSE(SE_ID::MIDDLE_WIND_SE);
}

Tornado::~Tornado()
{

}

void Tornado::Update()
{
	ACTIVITYTIME -= Time::DeltaTime;
	if (ACTIVITYTIME <= 0)
	{
		parameter.isDead = true;
		Sound::GetInstance().StopSE(SE_ID::STRONGWIND_SE);
		return;
	}

	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::STAGE_ACTOR, COL_ID::TORNADO_STAGE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR , COL_ID::TORNADO_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_BREAK_ACTOR, COL_ID::TORNADO_CASTLE_COL);
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::ISLAND_ACTOR , COL_ID::TORNADO_ISLAND_COL);


	isHit = false;

	//velocity.y = -GRAVITY;
	position += velocity * speed  * Time::DeltaTime;

	parameter.velocity = Vector3(velocity.x, 0.0f, velocity.z).Normalized() * speed;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::Translate(position);

	UpdateParticles();
}

void Tornado::Draw() const
{
	DrawParticles();
	
	//Vector3 TopPos, BottomPos;
	//BottomPos = Matrix4::GetPosition(parameter.mat);
	//TopPos = BottomPos + velocity * 1000.0f;

	DrawCapsule3D((position + parameter.height).ToVECTOR(), position, parameter.radius, 20, Vector3::Red.ToColor(), Vector3::Red.ToColor(), false);

	//DrawFormatString(10, 70, GetColor(255, 255, 255), "TopPoint	  : %f %f %f", TopPos.x, TopPos.y, TopPos.z);
	//DrawFormatString(10, 90, GetColor(255, 255, 255), "BottomPoint: %f %f %f", BottomPos.x, BottomPos.y, BottomPos.z);
	//DrawFormatString(10, 130, GetColor(255, 255, 255), "isHit		: %d", isHit);
}

void Tornado::OnCollide(Actor& other, CollisionParameter colpara)
{
	switch (colpara.colID){
	case COL_ID::TORNADO_STAGE_COL:
		//// ステージと衝突
		//position = colpara.colPos;
		//velocity.y = 0;
		break;
	case COL_ID::TORNADO_CASTLE_COL:
		//// 城と衝突
		//if (speed > 300.0f * 0.5f)
		//speed *= 0.5f;
		isHit = true;
		break;
	case COL_ID::TORNADO_ISLAND_COL:
		//// 浮島と衝突
		//if (speed > 300.0f * 0.5f)
		//speed *= 0.5f;
		//velocity.y = 0;
		////position = colpara.colPos;
		isHit = true;
		break;
	case COL_ID::SPHERE_SPHERE_COL:
		// 
		//velocity = colpara.colVelosity;
	case COL_ID::PLAYER_TORNADO_COL:
		velocity = Vector3(colpara.colVelosity.x, 0.0f, colpara.colVelosity.z).Normalized();
	default:
		break;
	}
}

void Tornado::Emissive()
{
	AddParticle(std::make_shared<TornadoParticle>(shared_from_this(),radius));
}