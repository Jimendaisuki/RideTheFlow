#pragma once
#include "Actor.h"
#include "../camera/Camera.h"
#include "../math/Vector3.h"

class CameraActor :public Actor
{
public:
	CameraActor(IWorld& world);
	~CameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
};