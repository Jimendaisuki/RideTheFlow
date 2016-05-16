#include "Effect.h"
#include "Blood.h"
#include "SpeedLine.h"
#include "../Def.h"
#include "../game/Random.h"
#include "../math/Vector2.h"


void Effect::DashEffect(IWorld& wo)
{
	if (Random::GetInstance().Range(0, 100) <= 80)
		wo.UIAdd(EFFECT_ID::SPEED_EFFECT, std::make_shared<SpeedLine>(wo, Random::GetInstance().Range(0.0f, 359.0f)));
}

void Effect::DashEffect(IWorld& wo, Vector3 position)
{
	if (Random::GetInstance().Range(0, 100) <= 80)
		wo.UIAdd(EFFECT_ID::SPEED_EFFECT, std::make_shared<SpeedLine>(wo, Random::GetInstance().Range(0.0f, 359.0f), position));
}

void Effect::StepEffect(IWorld& wo, EffectDirection ed)
{
	if (Random::GetInstance().Range(0, 100) <= 80)
	{
		switch (ed)
		{
		case Up:
			wo.UIAdd(EFFECT_ID::SPEED_EFFECT, std::make_shared<SpeedLine>(wo, Vector2(Random::GetInstance().Range(0.0f, (float)WINDOW_WIDTH), 0.0f), Vector2::Down, 90));
			break;
		case Down:
			wo.UIAdd(EFFECT_ID::SPEED_EFFECT, std::make_shared<SpeedLine>(wo, Vector2(Random::GetInstance().Range(0.0f, (float)WINDOW_WIDTH), (float)WINDOW_HEIGHT), Vector2::Up, -90));
			break;
		case Left:
			wo.UIAdd(EFFECT_ID::SPEED_EFFECT, std::make_shared<SpeedLine>(wo, Vector2(0.0f, Random::GetInstance().Range(0.0f, (float)WINDOW_HEIGHT)), Vector2::Right, 0));
			break;
		case Right:
			wo.UIAdd(EFFECT_ID::SPEED_EFFECT, std::make_shared<SpeedLine>(wo, Vector2((float)WINDOW_WIDTH, Random::GetInstance().Range(0.0f, (float)WINDOW_HEIGHT)), Vector2::Left, 180));
			break;
		default:
			break;
		}
	}
}

void Effect::DamegeEffect(IWorld& wo, const Vector3 position)
{
	wo.UIAdd(EFFECT_ID::BLOOD_EFFECT, std::make_shared<Blood>(wo, position));
}