#include "Failure.h"
#include "../math/Math.h"
#include "../time/Time.h"
#include "../world/IWorld.h"
#include "../UIactor/fadePanel/FadePanel.h"

const Vector2 DefScale = (WINDOW_WIDTH / 1920.0f, WINDOW_HEIGHT / 1080.0f);

Failure::Failure(IWorld& world_) :
UIActor(world_)
{
	parameter.isDead = false;
	parameter.id	 = UI_ID::FAILERE_UI;

	textAlpha = 0.0f;
	backAlpha = 0.0f;
	scale = 0.0f;
}

Failure::~Failure()
{

}

void Failure::Update()
{
	if (textAlpha < 1)
	{
		textAlpha += Time::DeltaTime / 6.0f;
		return;
	}
	textAlpha = 1;

	if (scale <= 5.0f)
		scale += Time::DeltaTime / 1.5f;
	scale = Math::Clamp(scale, 0.6f, 5.0f);

	if (backAlpha <= 1.0f)
		backAlpha += Time::DeltaTime / 2.0f;
	backAlpha = Math::Clamp(backAlpha, 0.0f, 1.0f);

	if ((backAlpha >= 1.0f) && 
		(!FadePanel::GetInstance().IsAction()))
	{
		FadePanel::GetInstance().SetOutTime(5.0f);
		FadePanel::GetInstance().FadeOut();
	}
}

void Failure::Draw() const
{
	float alpha = textAlpha - backAlpha * Math::Clamp(scale / 3.5f, 0.0f, 1.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::FAILED_BACK_1_SPRITE, Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2(1574.0f, 967.0f) / 2, backAlpha, DefScale * scale, 0, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::FAILED_SPRITE, Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vector2(650.0f, 175.0f) / 2, alpha, Vector2::One, true, false);
}