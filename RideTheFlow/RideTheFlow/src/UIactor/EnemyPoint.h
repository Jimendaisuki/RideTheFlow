#pragma once
#include "UIActor.h"
#include "../actor/Actor.h"

class EnemyPoint : public UIActor
{
public:
	EnemyPoint(IWorld& world, Actor& enemy);
	~EnemyPoint();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	// �G�l�~�[
	Actor*	enemy;
	// �X�P�[��
	float	scale;
	// �`��ʒu
	Vector2	drawPosition;
};