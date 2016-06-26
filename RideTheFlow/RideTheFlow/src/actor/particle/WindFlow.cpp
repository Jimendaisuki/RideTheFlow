#include "WindFlow.h"
#include "../Collision.h"
#include <algorithm>
#include "WindFlowParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"
#include "../../sound/Sound.h"

//タックルされた後の移動速度
static const float MoveSpeed = 400.0f;

WindFlow::WindFlow(IWorld& world, Player& player_) :
Actor(world),
player(player_),
isSetting(false),
vec(Vector3::Zero),
speed(MoveSpeed)
{
	parameter.id = ACTOR_ID::WIND_ACTOR;
	parameter.isDead = false;
	parameter.height = Vector3(0.0f, HeightMax, 0.0f);
	parameter.radius = 10.0f;
	ps_parameter.intervalSec = 0.003f;
	ps_parameter.lifeTimeLimit = 20.0f;
	ps_parameter.sameEmissiveNum = 1;
	dashPositions = player.ReturnDashPosStorage();

	Sound::GetInstance().PlaySE(SE_ID::MIDDLE_WIND_SE);
}
WindFlow::~WindFlow()
{

}
void WindFlow::Update()
{
	//ダッシュ終了までは座標配列を更新
	int size = player.ReturnDashPosStorage().size();
	if (size > 0 && !isSetting)
	{
		dashPositions.clear();
		for (int i = 0; i < size; i++)
		{
			if (i % 5 == 0)
			{
				//地を這うように配置
				Vector3 pos = Vector3(player.ReturnDashPosStorage().at(i).x, HeightMin, player.ReturnDashPosStorage().at(i).z);
				dashPositions.push_back(pos);
			}
		}
	}
	//ダッシュ終了後は座標配列を更新しない
	else if (size == 0)
	{
		isSetting = true;
	}

	//パーティクル更新
	UpdateParticles();

	//タックルされたら移動
	move += vec * speed * Time::DeltaTime;

	//システム寿命が来たらアクターも寿命に
	if (ps_parameter.isDead)
		parameter.isDead = true;
}
void WindFlow::Draw() const
{
	DrawParticles();

	//for (Vector3 i : dashPositions)
	//{
	//	Vector3 top = i;
	//	top.y = HeightMax;
	//	Vector3 bottom = i;
	//	bottom.y = HeightMin;
	//	DrawCapsule3D(bottom.ToVECTOR(), top.ToVECTOR(), parameter.radius, 10, 1, 1, 0);
	//}
}
void WindFlow::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYER_WIND_COL)
	{
		vec = colpara.colVelosity;
	}
}

std::vector<Vector3>& WindFlow::GetDashPositions()
{
	return dashPositions;
}

Vector3& WindFlow::GetMoveVec()
{
	return move;
}

void WindFlow::Emissive()
{
	if (dashPositions.size() > 0)
		AddParticle(std::make_shared<WindFlowParticle>(*this,dashPositions, Random::GetInstance().Range(HeightMin, HeightMax)));
}