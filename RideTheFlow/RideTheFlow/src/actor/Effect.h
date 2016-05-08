#pragma once;
#include "../world/IWorld.h"
#include "../math/Vector3.h"

class Effect
{
private:
	Effect() = default;
	~Effect() = default;

public:
	static Effect &GetInstance(){
		static Effect e;
		return e;
	}

	// ダッシュエフェクト
	void DashEffect(IWorld& wa);
	void DashEffect(IWorld& wa, Vector3 position_);
};
