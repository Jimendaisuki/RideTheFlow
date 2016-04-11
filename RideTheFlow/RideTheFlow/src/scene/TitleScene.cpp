#include "TitleScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/Enemy.h"


//コンストラクタ
TitleScene::TitleScene()
{
}

//デストラクタ
TitleScene::~TitleScene()
{
}

//開始
void TitleScene::Initialize()
{
	mIsEnd = false;
	wa.Add(ACTOR_ID::ENEMY, std::make_shared<Enemy>());
}

void TitleScene::Update()
{
	if (CheckHitKeyAll()){
		mIsEnd = true;
	}
	wa.Update();
}

//描画
void TitleScene::Draw() const
{
	wa.Draw();
}

//終了しているか？
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene TitleScene::Next() const
{
	return Scene::GamePlay;
}

void TitleScene::End(){
	wa.Clear();
}