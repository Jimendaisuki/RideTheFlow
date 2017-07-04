#include "Froatinglsland3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../NoShipArea.h"
#include "FroatinglslandParameter.h"
#include "../../math/Math.h"

Froatinglsland3::Froatinglsland3(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :
Actor(world)
{
	parameter.HP = lslandHP;

	parameter.isDead = false;
	parameter.radius = 80*scale.x;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	//ëDÇ™ì¸ÇÁÇ»Ç¢ÇÊÇ§Ç…ê›íË
	float maxRadius = Math::Sqrt(70.0f * 70.0f + 90.0f * 90.0f) * scale.x;
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
		parameter.mat.GetPosition() + Vector3(0.0f, 0.0f, 0.0f),
		maxRadius, *this));
}

Froatinglsland3::~Froatinglsland3()
{
}

void Froatinglsland3::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_ISLAND_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::ENEMY_BULLET, COL_ID::LAND3_BULLET_COL);
	//ñ≥ìGéûä‘
	if (!isCol)
	{
		timer += Time::GetInstance().deltaTime();
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
}