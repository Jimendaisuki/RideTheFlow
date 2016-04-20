#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"

class Castle : public Actor
{
public:
	Castle(IWorld& world, Vector3 position, Vector3 scale);
	~Castle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3		scale;
	DWORD		color;
};