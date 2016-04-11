#include "GamePlayScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"


//コンストラクタ
GamePlayScene::GamePlayScene()
{
	//mIsEnd = false;
}

//デストラクタ
GamePlayScene::~GamePlayScene()
{
}

//開始
void GamePlayScene::Initialize()
{
	mIsEnd = false;
	wa.Add(ACTOR_ID::PLAYER,std::make_shared<Player>());
}

void GamePlayScene::Update()
{
	if (CheckHitKeyAll()){
		mIsEnd = true;
	}
	wa.Update();
}

//描画
void GamePlayScene::Draw() const
{
	wa.Draw();
}

//終了しているか？
bool GamePlayScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene GamePlayScene::Next() const
{
	return Scene::Title;
}

void GamePlayScene::End(){
	wa.Clear();
}