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
	// エネミー
	Actor*	enemy;
	// スケール
	float	scale;
	// 描画位置
	Vector2	drawPosition;
};