#include "GamePlayScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/CameraActor.h"

#include "../math/Vector2.h"
#include "../input/Keyboard.h"

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
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));
}

void GamePlayScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEY_INPUT_SPACE)){
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