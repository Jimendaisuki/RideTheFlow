#include "EnemyHP.h"
#include "../time/Time.h"
#include "../graphic/Model.h"
#include "../graphic/BlendMode.h"
#include "../camera/Camera.h"

const float DELAY_TIME = 5.0f;

EnemyHP::EnemyHP() :
maxHP_(0.0f),
nowHP_(0.0f),
prevHP_(0.0f),
alpha_(0.0f),
position_(Vector3::Zero)
{
}

void EnemyHP::Initialize(const float& hp, const Vector3& position, const bool draw)
{
	isDraw_ = draw;
	maxHP_ = hp;
	nowHP_ = maxHP_;
	prevHP_ = nowHP_;
	position_ = position;
}

void EnemyHP::Update(const float& nowHp, const Vector3& position)
{
	if (!isDraw_) return;

	nowHP_ = nowHp;
	position_ = position;

	int now = nowHP_;
	int prev = prevHP_;
	if (nowHP_ != prev)
		alpha_ = 1.0f + DELAY_TIME;

	if (alpha_ >= 0.0f)
		alpha_ -= Time::DeltaTime;
	else
		alpha_ = 0.0f;

	prevHP_ = nowHP_;
}

void EnemyHP::Draw() const
{
	if (!isDraw_ || alpha_ <= 0.0f) return;

	auto front = (Camera::GetInstance().Target.Get() - Camera::GetInstance().Position.Get()) * Vector3(1.0f, 0.0f, 1.0f);
	auto left = Vector3::Normalize(Vector3::Cross(Vector3::Up, front));
	auto v = -left * 100.0f + Vector3(0.0f, 100.0f, 0.0f);

	float size = nowHP_ / maxHP_ * 200.0f;
	static int frontHandle = Model::GetInstance().GetHandle2D(MODEL_ID::LIFE_GAUGE_FRONT_2D);
	static int backHandle = Model::GetInstance().GetHandle2D(MODEL_ID::LIFE_GAUGE_BACK_2D);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0f * alpha_);
	DrawModiBillboard3D(position_ + v, 0.0f, 0.0f, 200.0f, 0.0f, 200.0f, 5.0f, 0.0f, 5.0f, backHandle, true);
	auto red = 510.0f * (1.0f - nowHP_ / maxHP_);
	auto green = 510.0f * (nowHP_ / maxHP_);
	SetDrawBright(red, green, 0.0f);
	DrawModiBillboard3D(position_ + v, 0.0f, 0.0f, size, 0.0f, size, 5.0f, 0.0f, 5.0f, frontHandle, true);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0.0f);
}