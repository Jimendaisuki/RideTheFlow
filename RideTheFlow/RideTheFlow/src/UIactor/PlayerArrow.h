#pragma once
#include "UIActor.h"
#include "../actor/Player.h"
#include <array>

class PlayerArrow : public UIActor
{
public:
	PlayerArrow(IWorld& world, Player* player);
	~PlayerArrow();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	// プレイヤーポインタ
	Player*		player;
	// 描画ポジション
	Vector2		drawPos_;
	// 回転角度
	float		angle_;
	// ダッシュフラグ
	bool		isDash;
	// 前フレームダッシュフラグ
	bool		prevDash;
	// 分割リソースハンドル
	std::array<int, 10>	resPiece;
};