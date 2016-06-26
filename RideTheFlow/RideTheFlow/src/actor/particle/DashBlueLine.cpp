#include "DashBlueLine.h"
#include "../Collision.h"
#include <algorithm>
#include "DashBlueLineParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"
#include "../../input/Keyboard.h"
#include "../../input/GamePad.h"

//タックルされた後の移動速度
static const float MoveSpeed = 400.0f;

DashBlueLine::DashBlueLine(IWorld& world, Player& player_) :
Actor(world),
player(player_),
isSetting(false),
vec(Vector3::Zero),
speed(MoveSpeed),
dashButtonState(true)
{
	parameter.id = ACTOR_ID::WIND_ACTOR;
	parameter.isDead = false;
	parameter.height = Vector3(0.0f, HeightMax, 0.0f);
	parameter.radius = 10.0f;
	ps_parameter.intervalSec = 0.05f;
	ps_parameter.lifeTimeLimit = 100.0f;
	ps_parameter.sameEmissiveNum = 1;
	dashPositions = player.ReturnDashPosStorage();
}
DashBlueLine::~DashBlueLine()
{

}
void DashBlueLine::Update()
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
				//配置
				Vector3 pos = Vector3(player.ReturnDashPosStorage().at(i).x, HeightMin, player.ReturnDashPosStorage().at(i).z);
				dashPositions.push_back(pos);
			}
		}
	}
	//ダッシュ終了後は死亡
	else if (size == 0)
	{
		ps_parameter.isDead = true;
	}

	//パーティクル更新
	UpdateParticles();

	//システム寿命が来たらアクターも寿命に
	if (ps_parameter.isDead)
		parameter.isDead = true;
}
void DashBlueLine::Draw() const
{
	DrawParticles();
}
void DashBlueLine::OnCollide(Actor& other, CollisionParameter colpara)
{
	
}

std::vector<Vector3>& DashBlueLine::GetDashPositions()
{
	return dashPositions;
}

Vector3& DashBlueLine::GetMoveVec()
{
	return move;
}

void DashBlueLine::Emissive()
{
	if (dashPositions.size() > 0)
		AddParticle(std::make_shared<DashBlueLineParticle>(dashPositions, player.GetParameter().mat.GetPosition().y));
}