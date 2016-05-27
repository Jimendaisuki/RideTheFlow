#include "FadePanel.h"
#include "../../graphic/Sprite.h"
#include "../../math/Math.h"
#include "../../time/Time.h"
#include "../../Def.h"

float time = 0;
float actionTime = 0;
float alpha = 1;
Vector2 scale = Vector2::Zero;
bool isAction = false;
bool isIn = true;
const Vector2 HD = Vector2(1920, 1080);
const Vector2 resSize = Vector2(1920, 1080);

void FadePanel::Initialize()
{
	/* èâä˙ê›íË */
	scale.x = (float)WINDOW_WIDTH / HD.x;
	scale.y = (float)WINDOW_HEIGHT / HD.y;
	isAction = false;
	alpha = 1;
	time = 0;
	actionTime = 0;

	isIn = true;
}

void FadePanel::Update()
{
	if (!isAction) return;

	if (time <= 0.0f) isAction = false;
	else
	{
		time -= Time::DeltaTime;
		if (isIn)	alpha -= (Time::DeltaTime / actionTime);
		else		alpha += (Time::DeltaTime / actionTime);
	}

	alpha = Math::Clamp(alpha, 0.0f, 1.0f);
}

void FadePanel::Draw()const
{
	Sprite::GetInstance().Draw(SPRITE_ID::DAMAGE_SPRITE, Vector2::Zero, Vector2::Zero, alpha, scale, 0.0f, true, false);
}

void FadePanel::FadeIn(float sec_)
{
	isAction = true;
	isIn = true;
	actionTime = sec_;
	time = actionTime;
}

void FadePanel::FadeOut(float sec_)
{
	isAction = true;
	isIn = false;
	actionTime = sec_;
	time = actionTime;
}

bool FadePanel::IsAction()
{
	return isAction;
}