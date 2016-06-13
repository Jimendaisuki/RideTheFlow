#pragma once
#include "UIActor.h"

class Clear : public UIActor
{
public:
	Clear(IWorld& world);
	~Clear();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	float	textAlpha;
	float	subAlpha;
	float	scale;
};