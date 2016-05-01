#include "TeamLogoScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/AnimTestActor.h"
#include "../actor/CameraActor.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"

//コンストラクタ
TeamLogoScene::TeamLogoScene()
{
}

//デストラクタ
TeamLogoScene::~TeamLogoScene()
{
}

//開始
void TeamLogoScene::Initialize()
{
	mIsEnd = false;
}

void TeamLogoScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}
	wa.Update();
}

//描画
void TeamLogoScene::Draw() const
{
	TextDraw::GetInstance().Draw("チームロゴシーン スペースキーでタイトルシーンへ");
	wa.Draw();
}

//終了しているか？
bool TeamLogoScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene TeamLogoScene::Next() const
{
	return Scene::Title;
}

void TeamLogoScene::End(){
	wa.Clear();
}