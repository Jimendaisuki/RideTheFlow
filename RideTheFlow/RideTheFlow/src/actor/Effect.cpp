#include "Effect.h"
#include "IntensiveLine.h"
#include "../Def.h"
#include "../game/Random.h"


void Effect::DashEffect(IWorld& wo)
{
	if (Random::GetInstance().Range(0, 100) <= 80)
		wo.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<IntensiveLine>(wo, Random::GetInstance().Range(0.0f, 359.0f)));
}

void Effect::DashEffect(IWorld& wo, Vector3 position)
{
	if (Random::GetInstance().Range(0, 100) <= 80)
		wo.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<IntensiveLine>(wo, Random::GetInstance().Range(0.0f, 359.0f), position));
}

void Effect::StepEffect(IWorld& wo, EffectDirection ed)
{
	if (Random::GetInstance().Range(0, 100) <= 80)
	{
		switch (ed)
		{
		case Up:
			wo.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<IntensiveLine>(wo, Vector2(Random::GetInstance().Range(0.0f, (float)WINDOW_WIDTH), 0.0f), Vector2::Down, 90));
			break;
		case Down:
			wo.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<IntensiveLine>(wo, Vector2(Random::GetInstance().Range(0.0f, (float)WINDOW_WIDTH), (float)WINDOW_HEIGHT), Vector2::Up, -90));
			break;
		case Left:
			wo.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<IntensiveLine>(wo, Vector2(0.0f, Random::GetInstance().Range(0.0f, (float)WINDOW_HEIGHT)), Vector2::Right, 0));
			break;
		case Right:
			wo.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<IntensiveLine>(wo, Vector2((float)WINDOW_WIDTH, Random::GetInstance().Range(0.0f, (float)WINDOW_HEIGHT)), Vector2::Left, 180));
			break;
		default:
			break;
		}
	}
}