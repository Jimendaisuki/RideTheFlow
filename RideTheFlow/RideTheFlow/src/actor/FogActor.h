#pragma once
#include "Actor.h"

//ステージにかかるフォグを制御
class FogActor :public Actor
{
public:
	FogActor(IWorld& world);
	~FogActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
	float fogTotalPower;
	float angle;

	//どの角度からフォグをかけるか
	float
};