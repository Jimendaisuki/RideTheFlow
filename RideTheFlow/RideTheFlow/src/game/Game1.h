#pragma once

#include "GameFrame.h"
#include "Content.h"
#include "../input/Keyboard.h"
#include "../input/GamePad.h"
#include "../sound/Sound.h"
#include "../time/Time.h"
#include "../camera/Camera.h"
#include "../scene/SceneManager.h"
#include "Random.h"
#include <vector>

class Game1 : public GameFrame
{
public:
	Game1();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Finalize() override;
	virtual bool IsWait() const
	{
		return mIsLoaded;
	}

private:
	Time mTime;
	Content mContent;

	SceneManager mSceneManager;

	float effectTime;
	int mPixelShader; /* ピクセルシェーダーハンドル */
	int mRenderTarget; /* レンダーターゲット */
	bool mIsLoaded;
};