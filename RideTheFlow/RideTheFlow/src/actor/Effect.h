#pragma once;
#include "../world/IWorld.h"

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
};
