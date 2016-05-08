#include "Effect.h"
#include "IntensiveLine.h"
#include "../game/Random.h"


void Effect::DashEffect(IWorld& wa)
{
	if (Random::GetInstance().Range(0, 100) <= 80)
		wa.Add(ACTOR_ID::INTENSIVELINE_ACTOR, std::make_shared<IntensiveLine>(wa, Random::GetInstance().Range(0.0f, 359.0f)));
}