#include "TitleScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/Enemy.h"
#include "../actor/AnimTestActor.h"
#include "../actor/CameraActor.h"
#include "../input/Keyboard.h"
#include "../actor/castle/CastleBlock.h"
#include "../actor/tornado/Tornado.h"
#include "../game/Random.h"
#include "../graphic/TextDraw.h"

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
	wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0,-50,0), Vector3::Right));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));
}

void TitleScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z)){
		Vector3 pos;
		wa.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
			pos = other.GetParameter().mat.GetPosition();
		});
		wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<CastleBlock>(wa, pos, Random::GetInstance().Range(8.0f, 10.0f)));
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
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