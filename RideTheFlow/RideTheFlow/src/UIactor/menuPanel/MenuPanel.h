#pragma once
#include "../UIActor.h"
#include "../Beziers.h"
#include "../../math/Point.h"
#include "../../math/Vector2.h"
#include "../../scene/Scene.h"

enum MENU_STATUS
{
	BEGIN	= 0,
	OPEN	= 1,
	SELECT  = 2,
	MANUAL	= 3,
	CLOSE	= 4,
	END		= 5,
};

//class MenuPanel : public UIActor
//{
//public:
//	MenuPanel(IWorld& world, const Scene nowScene_);
//	~MenuPanel();
//	virtual void Update() override;
//	virtual void Draw() const override;
//	void DrawMenu() const;
//	void DrawPause() const;
//
//
//private:
//	/* 現在のシーン */
//	Scene	scene;
//	/* 基本設定 */
//	Vector2 scale;
//	Vector2 drawPosition;
//	float	time;
//	/* 巻物用変数 */
//	float	rollAlpha;
//	float	rollBakcAlpha;
//	float	moveVec;
//	Point	size;
//	/* テキスト用 */
//	float	textAlpha;
//	int		selectNum;
//	int		nowPage;
//	int		prePage;
//	/* ステータス */
//	MENU_STATUS status;
//
//	bool	isAction;
//	bool	isExit;
//
//	RECT	rect;
//	float	selects[3];
//	float	pages[5];
//
//	CBezier bez;
//};

class MenuPanel
{
private:
	MenuPanel() = default;
	~MenuPanel() = default;

public:
	static MenuPanel &GetInstance(){
		static MenuPanel m;
		return m;
	}

	void Initialize();
	void Update();
	void Draw();
	void DrawMenu() const;
	void DrawPause() const;
	void DrawManual() const;
	void Action(Scene scene_);
	bool IsEnd() const;
	bool IsBackSelect() const;
	void Close();


private:
	MENU_STATUS status;
	float	backAlpha;
	float	rollAlpha;
	float	rollBakcAlpha;
	float	textAlpha;
	float	time;
	float	moveVec;
	int		selectNum;
	float	selects[3];
	int		nowPage;
	int		prePage;
	float	pages[5];
	Vector2 drawPosition;
	Vector2 scale;
	bool	isAction;
	bool	isBackSelect;
	float	alphaTime;

	CBezier bez;
	Scene	scene;
	Point	size;
	RECT	rect;
};