#include "Cloud.h"
#include "../world/IWorld.h"
#include "Collision.h"
#include "../game/Random.h"
#include "../graphic/Model.h"
#include "../camera/Camera.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"

//描画する雲モデルの数
static const int CloudMaxNum = 10;

//サイズ
static const float MinSize = 100.0f;
static const float MaxSize = 200.0f;

//流れに流されている時の速度
static const float FlowSpeed = 250.0f;

Cloud::Cloud(IWorld& world, const Vector3& position_) :
Actor(world),
position(position_),
moveSpeed(Random::GetInstance().Range(50.0f, 60.0f)),
moveChangeTimer(0.0f),
moveChangeTime(Random::GetInstance().Range(30.0f, 50.0f)),
windOutTimer(500.0f),
up(Vector3::Up),
front(Vector3::Forward),
left(Vector3::Left)
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::CLOUD_ACTOR;
	parameter.radius = 300.0f;

	for (int i = 0; i < CloudMaxNum; i++)
	{
		cloudPositions.push_back(Vector3(
			Random::GetInstance().Range(-40.0f + i, 40.0f + i),
			Random::GetInstance().Range(-40.0f + i, 40.1f + i),
			Random::GetInstance().Range(-40.0f + i, 40.2f + i)));
		cloudsizes.push_back(Random::GetInstance().Range(MinSize + i, MaxSize));
	}

	moveVec = Vector3::Normalize(Vector3(
		Random::GetInstance().Range(-1.0f, 1.0f),
		0.0f,
		Random::GetInstance().Range(-1.0f, 1.0f)));
	
	////テクスチャのアルファを抜き取る
	//MV1SetMaterialDrawAlphaTestAll(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), true, DX_CMP_GREATEREQUAL, 100);
}
Cloud::~Cloud()
{
	
}

void Cloud::Update()
{
	//当たり判定セット
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CLOUD_WIND_COL);
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::CLOUD_TORNADO_COL);

	moveChangeTimer += Time::DeltaTime;
	windOutTimer += Time::DeltaTime;
	//一定時間に達した場合、ランダムに移動方向を変化させる
	if (moveChangeTimer >= moveChangeTime)
	{
		Reset();
	}
	//ステージの端に達した場合、原点に向かわせる
	if (IsStageOut())
	{
		Vector3 v = -parameter.mat.GetPosition();
		v.y = 0;
		v.Normalize();
		moveVec = v;
		moveSpeed = Random::GetInstance().Range(50.0f, 60.0f);
	}

	//流れから離れた場合、３秒かけてスピードを落とす
	if (windOutTimer <= 3.0f)
	{
		moveSpeed -= 80.0f * (3.0f - windOutTimer) * Time::DeltaTime;
	}

	//セルフビルボード計算
	up = Vector3::Normalize(Camera::GetInstance().Up.Get());
	front = Vector3::Normalize(Camera::GetInstance().Target.Get() - Camera::GetInstance().Position.Get());
	left = Vector3::Cross(up, front);
	parameter.mat.SetUp(up);
	parameter.mat.SetFront(front);
	parameter.mat.SetLeft(left);

	//移動
	position += moveVec * moveSpeed * Time::DeltaTime;
	parameter.mat.SetPosition(position);
}
void Cloud::Draw() const
{
	for (int i = 0; i < CloudMaxNum; i++)
	{
		Model::GetInstance().Draw(MODEL_ID::CLOUD_MODEL,
			parameter.mat.GetPosition() + cloudPositions.at(i), 0.4f, parameter.mat.GetRotateDegree(), cloudsizes.at(i), true);
	}

	////DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), parameter.radius, 4, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
}
void Cloud::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::CLOUD_WIND_COL)
	{
		moveVec = colpara.colVelosity;
		moveSpeed = FlowSpeed;
		moveChangeTimer = 0.0f;
		windOutTimer = 0.0f;
	}
	if (colpara.colID == COL_ID::CLOUD_TORNADO_COL)
	{
		parameter.isDead = true;
	}
}

void Cloud::Reset()
{
	moveChangeTimer = 0.0f;
	moveChangeTime = Random::GetInstance().Range(30.0f, 50.0f);
	moveVec = Vector3::Normalize(Vector3(
		Random::GetInstance().Range(-1.0f, 1.0f),
		0.0f,
		Random::GetInstance().Range(-1.0f, 1.0f)));
	moveSpeed = Random::GetInstance().Range(50.0f, 60.0f);
}

bool Cloud::IsStageOut()
{
	//原点から6000以上離れていれば場外
	return Vector3::Distance(Vector3::Zero, parameter.mat.GetPosition()) > 6000.0f;
}