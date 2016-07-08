#include "Damege.h"
#include "../math/Math.h"

const float deadTime  = 2.0f;
const float offset    = 20.0f;
const Vector2 HD	  = Vector2(1920, 1080);
const Vector2 resSize = Vector2(1920, 1080);

Damege::Damege(IWorld& world, float& HP_, float maxHP_) :
UIActor(world)
{
	parameter.isDead = false;
	parameter.id = UI_ID::DAMAGE_UI;

	/* èâä˙ê›íË */
	scale.x = (float)WINDOW_WIDTH / HD.x;
	scale.y = (float)WINDOW_HEIGHT / HD.y;

	nowHP = &HP_;
	maxHP = maxHP_;
}

Damege::~Damege()
{
	nowHP = nullptr;
}

void Damege::Update()
{

}

void Damege::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::DAMAGE_SPRITE, Vector2::Zero, Vector2::Zero, 1.0f - Math::Clamp(*nowHP / maxHP, 0.0f, 1.0f), scale, 0.0f, true, false);
}