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
	void DashEffect(IWorld& wo);
	void DashEffect(IWorld& wo, Vector3 position);
	void StepEffect(IWorld& wo, EffectDirection ed);

	void DamegeEffect(IWorld& wo, const Vector3 position);
};
