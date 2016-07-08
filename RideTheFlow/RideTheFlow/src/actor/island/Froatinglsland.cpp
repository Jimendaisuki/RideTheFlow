#include "Froatinglsland.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../NoShipArea.h"
#include "FroatinglslandParameter.h"
#include "../castle/MasterCastle.h"

Froatinglsland::Froatinglsland(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, bool isGameScene_) :
Actor(world),
isGameScene(isGameScene_)
{
	parameter.HP = lslandHP;

	parameter.isDead = false;
	parameter.radius = 90;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);

	if (!isGameScene_)
		return;

	//ëDÇ™ì¸ÇÁÇ»Ç¢ÇÊÇ§Ç…ê›íË
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world, 
		parameter.mat.GetPosition()+Vector3(0.0f,0.0f,0.0f),
		parameter.radius*scale.x, *this));

	DxLib::MV1SetupCollInfo(MODEL_ID::ISLE_1_MODEL, -1);

	parameter.handle = MV1DuplicateModel(Model::GetInstance().GetHandle(MODEL_ID::ISLE_1_MODEL));

}

Froatinglsland::~Froatinglsland()
{

}

void Froatinglsland::Update()
{
	if (!isGameScene)
		return;

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

void Froatinglsland::Draw() const
{
	Vector3 startPos = parameter.mat.GetPosition() - Vector3(0.0f, parameter.radius / 3, 0.0f);
	Vector3 endPos = parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius / 2, 0.0f);
	//DrawCapsule3D(startPos.ToVECTOR(), endPos.ToVECTOR(), parameter.radius, 10, 1, 1, FALSE);
	Model::GetInstance().Draw(MODEL_ID::ISLE_1_MODEL, parameter.mat);
}

void Froatinglsland::OnCollide(Actor& other, CollisionParameter colpara)
{
}