#include "CreditScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/CameraActor.h"

#include "../input/Keyboard.h"

#include "../actor/tornado/Tornado.h"
#include "../actor/castle/Castle.h"


//コンストラクタ
CreditScene::CreditScene()
{

	//mIsEnd = false;
}

//デストラクタ
CreditScene::~CreditScene()
{
}

//開始
void CreditScene::Initialize()
{
	mIsEnd = false;
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));

	wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0, 200, 0), Vector2(1, 1), Vector3(10, 0, 0)));
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(0, 25, 0), Vector3(0, 0, 0), Vector3(50, 50, 50)));
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(-100, -25, 0), Vector3(0, 45, 0), Vector3(50, 50, 50)));
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(0, -25, 0), Vector3(0, 60, 0), Vector3(50, 50, 50)));
	/*wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1)));*/

	MV1SetupCollInfo(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), -1, 8, 8, 8);
}

void CreditScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	wa.Update();
}

//描画
void CreditScene::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::STAGE_MODEL, Vector3::Zero, Vector3::Zero, Vector3(10.0f));

	DrawFormatString(10, 10, GetColor(255, 255, 255), "CreditScene");
	wa.Draw();
}

//終了しているか？
bool CreditScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene CreditScene::Next() const
{
	return Scene::Title;
}

void CreditScene::End(){
	wa.Clear();
}