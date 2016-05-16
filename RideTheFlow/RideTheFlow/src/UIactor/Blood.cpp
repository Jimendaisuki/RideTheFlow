#include "Blood.h"
#include "../game/Random.h"
#include "../math/Math.h"
#include "../time/Time.h"
#include "../Def.h"

const float deadTime = 2.0f;
const float offset = 20.0f;
Blood::Blood(IWorld& world, const Vector3 position_) :
UIActor(world)
{
	parameter.isDead = false;
	parameter.id	 = EFFECT_ID::BLOOD_EFFECT;

	/* ‰ŠúÝ’è */
	alpha     = 1.0f;
	alphaTime = deadTime;
	scale  = Vector2(0.5f) * Random::GetInstance().Range(0.5f, 1.5f);
	rotate = Random::GetInstance().Range(0.0f, 359.0f);

	/* ˆÊ’u‚ðŽZo */
	Vector3 temp = ConvWorldPosToScreenPos(position_.ToVECTOR());
	position = Vector2(
		Math::Clamp(temp.x, offset, (float)WINDOW_WIDTH - offset) + Random::GetInstance().Range(-20.0f, 20.0f),
		Math::Clamp(temp.y, offset, (float)WINDOW_HEIGHT - offset) + Random::GetInstance().Range(-20.0f, 20.0f));
	
	/* ƒJƒƒ‰‚Ì— ‘¤‚É‚¢‚½ê‡‚Ì•â³ */
	if (temp.z >= 1)
	{
		position.x = (WINDOW_WIDTH - position.x) + Random::GetInstance().Range(-20.0f, 20.0f);
		position.y = WINDOW_HEIGHT + Random::GetInstance().Range(-20.0f, 20.0f);
	}
}

Blood::~Blood()
{

}

void Blood::Update()
{
	if (alphaTime > 0)	alphaTime -= Time::DeltaTime;
	else alpha -= Time::DeltaTime;

	if (alpha <= 0) parameter.isDead = true;
}

void Blood::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::BLOOD_SPRITE, position, Vector2(262, 256), alpha, scale, rotate, true, false);
}