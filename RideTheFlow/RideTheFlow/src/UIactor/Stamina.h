#pragma once
#include "UIActor.h"
#include "../actor/Player.h"

class Stamina : public UIActor
{
public:
	Stamina(IWorld& world, float& maxStamina, float& nowStamina, Player& player);
	~Stamina();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	float*	maxStamina;
	float*	nowStamina;
	Vector2 scale;
	Player*	player;
};
