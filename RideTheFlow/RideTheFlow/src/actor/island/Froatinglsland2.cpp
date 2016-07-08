#include "Froatinglsland2.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../NoShipArea.h"
#include "FroatinglslandParameter.h"
#include "../castle/MasterCastle.h"
#include "../../math/Math.h"
Froatinglsland2::Froatinglsland2(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale,bool isGameFlag) :
Actor(world),
timer(0.0f),
isCol(true)
{

	parameter.HP = lslandHP;
	parameter.isDead = false;
	parameter.radius = 150;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);

	if (!isGameFlag) return;
	//ëDÇ™ì¸ÇÁÇ»Ç¢ÇÊÇ§Ç…ê›íË
	float maxRadius = Math::Sqrt(100.0f * 100.0f + 75.0f * 75.0f) * scale.x;
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
		parameter.mat.GetPosition() + Vector3(0.0f, 0.0f, 0.0f),
		parameter.radius*scale.x, *this));
	DxLib::MV1SetupCollInfo(MODEL_ID::ISLE_2_MODEL, -1);
	parameter.handle = MV1DuplicateModel(Model::GetInstance().GetHandle(MODEL_ID::ISLE_2_MODEL));
}

Froatinglsland2::~Froatinglsland2()
{

}

void Froatinglsland2::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_ISLAND_COL);
	//ñ≥ìGéûä‘
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

void Froatinglsland2::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::ISLE_2_MODEL, parameter.mat);
}

void Froatinglsland2::OnCollide(Actor& other, CollisionParameter colpara)
{

}