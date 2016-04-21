#include "GamePlayScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/CameraActor.h"

#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include "../actor/tornado/Tornado.h"


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
//	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(Vector3(0.0f,0.0f, -150.0f));
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();
	
	//wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0, 0, 0), Vector3(10, 0, 0)));
}

void GamePlayScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
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
	return Scene::Ending;
}

void GamePlayScene::End(){
	wa.Clear();
}