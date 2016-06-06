#pragma once
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
	void Draw(Scene scene) const;
	void DrawMenu() const;
	void DrawPause() const;
	void DrawManual() const;
	void Action();

private:
	MENU_STATUS status;

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

	Point	size;
	RECT	rect;
	CBezier bez;
};