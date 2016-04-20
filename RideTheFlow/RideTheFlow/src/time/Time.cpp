#include "Time.h"
#include "../math/Math.h"
#include <Dxlib.h>
#include "../Def.h"

float Time::DeltaTime;

Time::Time()
:
savetime(0)
{

}

// XVˆ—
void Time::Update()
{
	DeltaTime = (float)((GetNowCount() - Math::Abs(savetime)) / 1000.0f);

	savetime = GetNowCount();
}