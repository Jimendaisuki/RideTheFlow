#include "FadePanel.h"
#include "../../graphic/Sprite.h"
#include "../../math/Math.h"
#include "../../time/Time.h"
#include "../../Def.h"

const Vector2 HD = Vector2(1920, 1080);
const Vector2 resSize = Vector2(800, 600);

void FadePanel::Initialize()
{
	/* 初期設定 */
	scale.x = (float)WINDOW_WIDTH  / resSize.x;
	scale.y = (float)WINDOW_HEIGHT / resSize.y;
	isAction = false;
	alpha = 1.0f;
	maxAlpha = 1.0f;
	actionTime = 0;
	status = FADE_STATUS::STANDBY;
}

void FadePanel::Update()
{
	if (!isAction) return;

	switch (status)
	{
	case FADE_STATUS::FadeIn:
		alpha -= (Time::DeltaTime / actionTime);
		if (IsFullClear()) status = FADE_STATUS::STANDBY;
		break;
	case FADE_STATUS::FadeOut:
		alpha += (Time::DeltaTime / actionTime);
		if (IsFullBlack()) status = FADE_STATUS::STANDBY;
		break;
	default:
		isAction = false;
		break;
	}

	// 一応抜け出し用
	if (alpha < 0.0f || maxAlpha < alpha) status = FADE_STATUS::STANDBY;
	// アルファクランプ
	alpha = Math::Clamp(alpha, 0.0f, maxAlpha);
}

void FadePanel::Draw()const
{
	Sprite::GetInstance().Draw(SPRITE_ID::BLACK_SCREEN, Vector2::Zero, Vector2::Zero, alpha, scale, 0.0f, false, false);
}

void FadePanel::FadeIn(float sec_)
{
	status = FADE_STATUS::FadeIn;
	isAction = true;
	actionTime = sec_;
}

void FadePanel::FadeOut(float sec_, float maxAlpha_)
{
	status = FADE_STATUS::FadeOut;
	maxAlpha = maxAlpha_;
	isAction = true;
	actionTime = sec_;
}

bool FadePanel::IsAction() const
{
	return isAction;
}

bool FadePanel::IsFullBlack() const
{
	return alpha >= 1.0f;
}

bool FadePanel::IsFullClear() const
{
	return alpha <= 0.0f;
}
