#pragma once
#include "Actor.h"

class Enemy :public Actor
{
public:
	Enemy(IWorld& world,Vector3 position);
	~Enemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	int tex;
	Matrix4 playerMat;
	float coolTime;
	float time;
	bool attack;
	Vector3 mPosition;
};