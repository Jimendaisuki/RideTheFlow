#pragma once
#include "UIActor.h"
#include "MiniMap.h"
#include "../actor/Player.h"
#include <array>

class FlowRoot : public UIActor
{
	struct DrawPoints
	{
		Point	p1;
		Point	p2;
		Point	p3;
		Point	p4;
	};
public:
	FlowRoot(IWorld& world_, Player* player_, Vector2* point_, std::array<int, 10> piece);
	~FlowRoot();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	// プレイヤーポインタ
	Player*		player;
	// プレイヤーアローポジションポインタ
	Vector2*	arrowPos;
	// 描画用４点
	DrawPoints	p;
	// フレームカウント
	int			count;
	// 流れカウント
	float			flowCount;
	// 流れ終了時間
	float		deadTime;
	// 終了フラグ
	bool		isEnd;
	// 分割リソースハンドル配列
	std::array<int, 10>		resPiece;
	// プレイヤー軌跡リスト
	std::list<Point>		playerTraces;
	// 軌跡描画用ポイントリスト
	std::list<DrawPoints>	drawPoints;
};