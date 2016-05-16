#pragma once
#include "UIActor.h"
#include "../math/Vector3.h"

class Damege : public UIActor
{
public:
	Damege(IWorld& world);
	~Damege();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	float	maxHP;
	float	nowHP;
	Vector2 scale;
};