#include "TeamLogoScene.h"
#include "../AllInclude.h"
#include "Scene.h"
#include "../input/Keyboard.h"
#include "../graphic/Sprite.h"
#include "../Def.h"

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
	mIsEnd = true;
	wa.Update();
}

//描画
void TeamLogoScene::Draw() const
{
	wa.Draw();
	Sprite::GetInstance().Draw(SPRITE_ID::LOADING_SPRITE, Vector2(WINDOW_WIDTH - 700.0f, WINDOW_HEIGHT - 125.0f));
}

//終了しているか？
bool TeamLogoScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene TeamLogoScene::Next() const
{
	return Scene::Ending;
}

void TeamLogoScene::End(){
	wa.Clear();
}