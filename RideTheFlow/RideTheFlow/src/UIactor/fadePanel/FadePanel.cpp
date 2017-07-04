#include "FadePanel.h"
#include "../../graphic/Sprite.h"
#include "../../math/Math.h"
#include "../../time/Time.h"
#include "../../Def.h"

const Vector2 scale = Vector2((float)WINDOW_WIDTH / 800, (float)WINDOW_HEIGHT / 600);

void FadePanel::Initialize()
{
	/* 初期設定 */
	isAction = false;
	alpha		= 1.0f;
	maxAlpha	= 1.0f;
	actionTime	= 0;
	inTime = 1.0f;
	outTime = 1.0f;
	status = FADE_STATUS::STANDBY;
}

void FadePanel::Update()
{
	if (!isAction) return;

	switch (status)
	{
	case FADE_STATUS::FadeIn:
		alpha -= (Time::GetInstance().deltaTime() / actionTime);
		if (IsFullClear()) status = FADE_STATUS::STANDBY;
		break;
	case FADE_STATUS::FadeOut:
		alpha += (Time::GetInstance().deltaTime() / actionTime);
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

void FadePanel::FadeIn()
{
	status = FADE_STATUS::FadeIn;
	actionTime = GetInTime();
	isAction = true;
}

void FadePanel::FadeOut(float maxAlpha_)
{
	status = FADE_STATUS::FadeOut;
	maxAlpha = maxAlpha_;
	actionTime = GetOutTime();
	isAction = true;
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
