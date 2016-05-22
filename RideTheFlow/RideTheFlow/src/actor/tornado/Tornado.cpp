#include "Tornado.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../castle/CastleBlock.h"

#include "../../input/Keyboard.h"
#include "../particle/TornadoParticle.h"


const float TornadoDefaltSpeed = 300.0f;
Tornado::Tornado(IWorld& world, Vector3 position_, Vector2 scale_, Vector3 velocity_) :
Actor(world),
position(position_),
velocity(velocity_),
timer(0.0f)
{
	ACTIVITYTIME = 20.0f;
	GRAVITY = 3.0f;
	speed = 300.0f;

	parameter.isDead = false;
	parameter.height = Vector3(0.0f,200.0f,0.0f);
	parameter.radius = 80;
	parameter.mat =
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	parameter.id = ACTOR_ID::TORNADO_ACTOR;

	ps_parameter.intervalSec = 0.1f;
	ps_parameter.lifeTimeLimit = 9999.0f;
	ps_parameter.sameEmissiveNum = 2;
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

	velocity.y = -GRAVITY;
	position += velocity * speed  * Time::DeltaTime;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	UpdateParticles();
}

void Tornado::Draw() const
{
	DrawParticles();
	
	//Vector3 TopPos, BottomPos;
	//BottomPos = Matrix4::GetPosition(parameter.mat);
	//TopPos = BottomPos + velocity * 1000.0f;

	//DrawFormatString(10, 70, GetColor(255, 255, 255), "TopPoint	  : %f %f %f", TopPos.x, TopPos.y, TopPos.z);
	//DrawFormatString(10, 90, GetColor(255, 255, 255), "BottomPoint: %f %f %f", BottomPos.x, BottomPos.y, BottomPos.z);
	//DrawFormatString(10, 130, GetColor(255, 255, 255), "isHit		: %d", isHit);
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
		for (int i = 0; i < 3; i++){
			world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleBlock>(world, parameter.mat.GetPosition()));
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

void Tornado::Emissive()
{
	AddParticle(std::make_shared<TornadoParticle>(shared_from_this()));
}