#include "Game1.h"
#include "../AllInclude.h"
#include "../scene/SceneManager.h"
#include "../scene/TitleScene.h"
#include "../scene/GamePlayScene.h"
#include "../Def.h"
#include <thread>

Game1::Game1() :
mKeyboard(), 
mGamepad(),
effectTime(0.0f),
mAnime(mModel),
mPixelShader(-1), 
mRenderTarget(-1),
mIsLoaded(false)
{

}

void Game1::Initialize()
{
	mIsLoaded = false;
	mModel.Initialize();
	mSprite.Initialize();
	mSound.Initialize();

	// ファイルの読み込み
	mContent.LoadSprite(mSprite, mModel);
	//mContent.LoadSound(mSound);
	//mContent.LoadModel(mModel,false);

	mSceneManager.Add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	mSceneManager.Add(Scene::Title, std::make_shared<TitleScene>());
	mSceneManager.SetScene(Scene::Title);
}

void Game1::Update()
{
	// 時間を更新
	mTime.Update();

	// 入力の更新
	mKeyboard.Update();
	mGamepad.Update();
	// Escキー入力で強制終了
	if (mKeyboard.KeyTriggerDown(KEY_INPUT_ESCAPE) ||
		(mGamepad.ButtonStateDown(PAD_INPUT_9) && mGamepad.ButtonStateDown(PAD_INPUT_10)))
	{
		GameFrame::GameEnd();
		return;
	}

	// シーンが変更されているかを確認
	mSceneManager.Change();
	// シーンを更新
	mSceneManager.Update();
}

void Game1::Draw()
{
	// シーンを描画
	mSceneManager.Draw();
}

void Game1::Finalize()
{
	mSceneManager.End();
	DeleteShader(mPixelShader);
	DeleteGraph(mRenderTarget);
}