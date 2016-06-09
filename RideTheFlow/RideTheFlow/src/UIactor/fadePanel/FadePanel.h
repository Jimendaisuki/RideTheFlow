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
	// �ψْ����H
	bool IsAction() const;
	// ��ʂ��^���Â��H
	bool IsFullBlack() const;
	// ��ʂ������Ȃ����H
	bool IsFullClear() const;

private:
	FADE_STATUS status;

	float	actionTime;
	float	alpha;
	float	maxAlpha;
	bool	isAction;
	Vector2 scale;
};