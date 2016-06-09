#pragma once
#include "../../math/Vector2.h"

enum FADE_STATUS
{
	STANDBY	= 0,
	FadeIn	= 1,
	FadeOut = 2
};

class FadePanel
{
private:
	FadePanel() = default;
	~FadePanel() = default;

public:
	static FadePanel &GetInstance(){
		static FadePanel f;
		return f;
	}

	void Initialize();
	void Update();
	void Draw() const;
	void FadeIn(float sec);
	void FadeOut(float sec, float maxAlpha = 1.0f);
	// 変異中か？
	bool IsAction() const;
	// 画面が真っ暗か？
	bool IsFullBlack() const;
	// 画面が黒くないか？
	bool IsFullClear() const;

private:
	FADE_STATUS status;

	float	actionTime;
	float	alpha;
	float	maxAlpha;
	bool	isAction;
	Vector2 scale;
};