#pragma once
#include "UIActor.h"

class Failure : public UIActor
{
public:
	Failure(IWorld& world);
	~Failure();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	float	textAlpha;
	float	backAlpha;
	float	scale;
	float	bgmVol;
};