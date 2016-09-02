#include "PVScene.h"
#include "../AllInclude.h"
#include "../Def.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../sound/Sound.h"
#include "../game/WorkFolder.h"
#include "../math/Math.h"
#include "../time/Time.h"

#include "../UIactor/fadePanel/FadePanel.h"

#define FILE_NAME  "気龍_PV.avi"
#define MOVIE_NAME "気龍_PV"

//コンストラクタ
PVScene::PVScene()
{
}

//デストラクタ
PVScene::~PVScene()
{
	
}

//開始
void PVScene::Initialize()
{
	mIsEnd = false;
	WorkFolder::SetWorkFolder("res/");
	movie.Load(FILE_NAME);
	movie.Seek(MOVIE_NAME, 1.0f);
	movie.Play(MOVIE_NAME);

	/* フェード */
	FadePanel::GetInstance().SetInTime(1.0f);
	FadePanel::GetInstance().SetOutTime(1.0f);
}

void PVScene::Update()
{
	/* イベントカット */
	if ((!FadePanel::GetInstance().IsAction()) &&
		(GamePad::GetInstance().AnyTriggerDown() ||
		 Keyboard::GetInstance().AnyTriggerDown()))
	{
		FadePanel::GetInstance().FadeOut();
	}
	if (!FadePanel::GetInstance().IsAction() &&
		FadePanel::GetInstance().IsFullBlack())
	{
		mIsEnd = true;
		return;
	}

	auto time = movie.IsTime(MOVIE_NAME);
	if (time >= PV_END_TIME && !FadePanel::GetInstance().IsAction())
		FadePanel::GetInstance().FadeOut();
}

//描画
void PVScene::Draw() const
{
	movie.Draw();
}

//終了しているか？
bool PVScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene PVScene::Next() const
{
	return Scene::Title;
}

void PVScene::End()
{
	wa.Clear();
	movie.Clear();
}
