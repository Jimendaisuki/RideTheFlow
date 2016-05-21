#pragma once;
#include "../world/IWorld.h"

class Vector3;

enum EffectDirection
{
	Up,
	Down,
	Left,
	Right
}; 

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
	void DashEffect(IWorld& wa, Vector3 position);
	void StepEffect(IWorld& wa, EffectDirection ed);

	void DamegeEffect(IWorld& wo, const Vector3 position, const Vector3 front);
	void DamegeEffect(IWorld& wo, const Vector3 position, const Actor& player_);
};
