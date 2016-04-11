#pragma once
#include "Actor.h"

class Player :public Actor
{
public:
	Player();
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other) override;

private:
	int tex;
};