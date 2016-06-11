#include "Clear.h"
#include "../time/Time.h"
#include "../math/Math.h"

const Vector2 DrawPosition = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

Clear::Clear(IWorld& world_) :
UIActor(world_)
{
	parameter.isDead = false;
	parameter.id = UI_ID::CLEAR_UI;

	textAlpha = 0.0f;
	subAlpha  = 0.0f;
}

Clear::~Clear()
{

}

void Clear::Update()
{
	if (textAlpha < 1)
	{
		textAlpha += Time::DeltaTime / 2.0f;
		return;
	}
	textAlpha = 1;

	if (subAlpha < 1)
	{
		subAlpha += Time::DeltaTime / 2.0f;
		return;
	}
	parameter.isDead = true;
}

void Clear::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::CLEAR_SPRITE, DrawPosition, Vector2(650.0f, 175.0f) / 2, textAlpha - subAlpha, Vector2::One, true, false);
}