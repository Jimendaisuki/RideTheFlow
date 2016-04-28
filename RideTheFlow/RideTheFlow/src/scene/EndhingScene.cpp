#include"EndhingScene.h"
#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include"../actor/SpringCameraActor.h"
#include "../actor/Player.h"
#include "../actor/castle/MasterCastle.h"
#include "../camera/Camera.h"
//コンストラクタ
EndhingScene::EndhingScene()
{
	timeTest = 0;
	//mIsEnd = false;
	position = Vector3::Zero;

}

//デストラクタ
EndhingScene::~EndhingScene()
{
}

//開始
void EndhingScene::Initialize()
{
	boonPositions.clear();
	mIsEnd = false;
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<SpringCameraActor>(wa));

	for (int i = 1; i < MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE)); i++)
	{
		if (i % 2 == 0)
		{
			Vector3 Position = Vector3::ToVECTOR(MV1GetFramePosition(Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE), i));
			boonPositions.push_back(Position);
		}
	}
 	for (auto i : boonPositions)
	{
		wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, i, Vector3(0), Vector3(30)));
	}
  	int num = MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE));
}

void EndhingScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	Camera::GetInstance().Update();
	wa.Update();
}

//描画
void EndhingScene::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::TEST_STAGE, Vector3::Zero, Vector3::Zero, Vector3(1.0f));
	//Model::GetInstance().Draw(MODEL_ID::SKY_MODEL, Vector3::Zero, Vector3::Zero, Vector3(5.0f));

	wa.Draw();
}

//終了しているか？
bool EndhingScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene EndhingScene::Next() const
{
	return Scene::Credit;
}

void EndhingScene::End(){
	boonPositions.clear();
	wa.Clear();
}