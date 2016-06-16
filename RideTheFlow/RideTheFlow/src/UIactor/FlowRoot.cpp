#include "FlowRoot.h"
#include "../math/Math.h"
#include "../world/IWorld.h"
#include "../time/Time.h"

const float WIDTH = 5 / 2;	// 横幅の半分
const float Scale = 0.6f;
const Vector2 MAP_POSITION = Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) - Vector2(256) * Scale;
const float ReSIZE = 256.0f / 3000.0f * Scale;


FlowRoot::FlowRoot(IWorld& world_, Player* player_, Vector2* point_, int piece[]) :
UIActor(world_),
player(player_),
arrowPos(point_),
count(0),
flowCount(0.0f),
deadTime(20.0f),
isEnd(false)
{
	parameter.id	 = UI_ID::FLOWROOT_UI;
	parameter.isDead = false;

	drawPoints.clear();
	playerTraces.clear();

	// ハンドル取得
	for (int i = 0; i < 10; i++)
		resPiece[i] = piece[i];

	/* 軌跡 */
	Vector2 temp = *arrowPos;
	playerTraces.push_back(temp.ToPoint());
}

FlowRoot::~FlowRoot()
{
	drawPoints.clear();
	playerTraces.clear();
	player = nullptr;
}

void FlowRoot::Update()
{
	// 発生時間
	if (deadTime > 0)
	{
		deadTime -= Time::DeltaTime;
		flowCount -= 0.5f;
	}
	else
		parameter.isDead = true;

	// ダッシュが終了していた場合更新終了
	if (isEnd) return;

	if (player->ReturnTackleParameter().dashFlag)
		count++;
	else
		isEnd = true;

	// 軌跡を保存
	if (count >= 10)
	{
		// 軌跡保存
		Vector2 temp = *arrowPos;
		if (Math::Abs(temp.x) < 0 || Math::Abs(temp.y) < 0) return;
		playerTraces.push_back(temp.ToPoint());
		// カウントリセット
		count = 0;
	}

	if (playerTraces.size() < 2) return;

	std::list<Point>::iterator it1, it2;
	int i = 0;
	drawPoints.clear();
	for (it1 = it2 = playerTraces.begin(), ++it2;
		it2 != playerTraces.end(); ++it1, ++it2)
	{
		if (i == 0)
		{	// 初回設定
			Vector2 v = Vector2(it2->x, it2->y) - Vector2(it1->x, it1->y);
			Vector2 n = Vector2(-v.y, v.x).Normalized();
			p.p1.x = it1->x + n.x * WIDTH;
			p.p1.y = it1->y + n.y * WIDTH;
			p.p2.x = it1->x - n.x * WIDTH;
			p.p2.y = it1->y - n.y * WIDTH;
		}
		else
		{	// 前フレーム流用
			p.p1 = p.p4;
			p.p2 = p.p3;
		}

		Vector2 v = Vector2(it2->x, it2->y) - Vector2(it1->x, it1->y);
		if (v.Length() != 0.0f)
		{
			Vector2 n = Vector2(-v.y, v.x).Normalized();
			p.p3.x = it2->x - n.x * WIDTH;
			p.p3.y = it2->y - n.y * WIDTH;
			p.p4.x = it2->x + n.x * WIDTH;
			p.p4.y = it2->y + n.y * WIDTH;

			drawPoints.push_back(p);
			i++;
		}
	}
}

void FlowRoot::Draw() const
{
	int i = 0;
	for (auto& point : drawPoints)
	{
		DrawModiGraphF(point.p1.x, point.p1.y, point.p2.x, point.p2.y, point.p3.x, point.p3.y, point.p4.x, point.p4.y, resPiece[(int)Math::Abs((i + (int)flowCount) % 10)], true);
		i++;
	}
}
