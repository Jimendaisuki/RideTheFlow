#pragma once
#include "UIActor.h"

class Damege : public UIActor
{
public:
	Damege(IWorld& world, float& HP_);
	~Damege();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	float	maxHP;
	float*	nowHP;
	Vector2 scale;
};