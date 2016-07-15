#include "Game1.h"
#include "../AllInclude.h"
#include "../scene/SceneManager.h"
#include "../scene/TeamLogoScene.h"
#include "../scene/TitleScene.h"
#include "../scene/MenuScene.h"
#include "../scene/EventScene.h"
#include "../scene/GamePlayScene.h"
#include "../scene/CreditScene.h"
#include "../scene/EndhingScene.h"
#include "../scene/PVScene.h"
#include "../Def.h"
#include "../graphic/Model.h"
#include "../graphic/Anime.h"
#include "../graphic/Sprite.h"
#include "../graphic/Movie.h"
#include <thread>

Game1::Game1() :
effectTime(0.0f),
mPixelShader(-1), 
mRenderTarget(-1),
mIsLoaded(false)
{

}

void Game1::Initialize()
{
	mIsLoaded = false;
	Model::GetInstance().Initialize();
	Sprite::GetInstance().Initialize();
	Sound::GetInstance().Initialize();

	// ファイルの読み込み
	mContent.LoadSprite(Sprite::GetInstance(), Model::GetInstance());
	mContent.LoadSound(Sound::GetInstance());
	mContent.LoadModel(Model::GetInstance(), false);

	mSceneManager.Add(Scene::Demo, std::make_shared<TeamLogoScene>());
	mSceneManager.Add(Scene::Title, std::make_shared<TitleScene>());
	mSceneManager.Add(Scene::Menu, std::make_shared<MenuScene>());
	mSceneManager.Add(Scene::Event, std::make_shared<EventScene>());
	mSceneManager.Add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	mSceneManager.Add(Scene::Ending, std::make_shared<EndhingScene>());
	mSceneManager.Add(Scene::Credit, std::make_shared<CreditScene>());
	mSceneManager.Add(Scene::PV, std::make_shared<PVScene>());

	mSceneManager.SetScene(Scene::Demo);
}

void Game1::Update()
{
	// 時間を更新
	mTime.Update();

	// 入力の更新
	Keyboard::GetInstance().Update();
	GamePad::GetInstance().Update();
	// Escキー入力で強制終了
	if (Keyboard::GetInstance().KeyTriggerDown(KEY_INPUT_ESCAPE))
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