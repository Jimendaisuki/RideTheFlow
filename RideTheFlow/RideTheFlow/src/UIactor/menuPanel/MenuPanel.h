#pragma once
#include "../UIActor.h"
#include "../Beziers.h"
#include "../../math/Point.h"
#include "../../math/Vector2.h"
#include "../../scene/Scene.h"
#include <array>

class MenuPanel
{
enum MENU_PANEL_STATUS
{
	BEGIN	= 0,
	OPEN	= 1,
	SELECT	= 2,
	MANUAL	= 3,
	CLOSE	= 4,
	PUSH	= 5,
	END		= 6,
	NONE	= 7,
};

public:
	MenuPanel(Scene currentScene);
	~MenuPanel();

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw() const;
	// 未実行なら実行させる
	void Action();
	// 実行中か？
	bool IsAction() const;
	// 戻るを押したか
	bool IsBackSelect() const;
	// 実行終了しているか？
	bool IsEnd() const;
	// 閉じる
	void Close();
	// 止める
	void Stop();

private:
	// メニューシーン用
	void DrawMenu() const;
	// ポーズシーン用
	void DrawPause() const;
	//
	void SetCloud();


private:
	MENU_PANEL_STATUS status;
	float	backAlpha;
	float	rollAlpha;
	float	rollBakcAlpha;
	float	alphaTime;
	float	textAlpha;
	float	time;
	float	moveVec;
	int		selectNum;
	std::array<float, 3> selects;
	int		nowPage;
	int		prePage;
	std::array<float, 5> pages;
	Vector2 drawPosition;
	float	textScale;
	bool	isAction;
	bool	isBackSelect;
	bool	isEnd;

	CBezier bez;
	Scene	scene;
	Point	size;
	RECT	rect;

	std::array<Vector2, 8>	tornadoPos;
	std::array<float, 8>	tornadoVel;
	float	tornadoAlpha;

	bool	isPush;
	int		currentButton;
};