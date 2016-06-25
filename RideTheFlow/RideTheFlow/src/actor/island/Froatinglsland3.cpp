#include "Froatinglsland3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../NoShipArea.h"
#include "FroatinglslandParameter.h"

Froatinglsland3::Froatinglsland3(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :
Actor(world)
{
	parameter.HP = lslandHP;

	parameter.isDead = false;
	parameter.radius = 120;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	//船が入らないように設定
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
		parameter.mat.GetPosition() + Vector3(0.0f, 0.0f, 0.0f),
		parameter.radius, *this));
}

Froatinglsland3::~Froatinglsland3()
{

}

void Froatinglsland3::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_ISLAND_COL);
	//無敵時間
	if (!isCol)
	{
		timer += Time::DeltaTime;
		if (timer >= lslandNoTimer)
		{
			isCol = true;
			timer = 0.0f;
		}
	}

	if (parameter.HP <= 0)
	{
		parameter.isDead = true;
	}
}

void Froatinglsland3::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::ISLE_3_MODEL, parameter.mat);
}

void Froatinglsland3::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::TORNADO_ISLAND_COL&&isCol)
	{
		parameter.HP -= lslandDamage;
		isCol = false;
	}
}