#pragma once
#include "Actor.h"

class Enemy :public Actor
{
public:
	Enemy();
	~Enemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other) override;

private:
	int tex;
};