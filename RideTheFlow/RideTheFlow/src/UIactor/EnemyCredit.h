#pragma once
#include "UIActor.h"

class EnemyCredit : public UIActor
{
public:
	EnemyCredit(IWorld& world);
	~EnemyCredit();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	//
	int		shipCount_;
	//
	int		castleCount_;
};