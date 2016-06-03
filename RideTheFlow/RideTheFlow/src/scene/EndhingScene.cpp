#include"EndhingScene.h"
#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include"../actor/MonhanCameraActor.h"
#include "../actor/Player.h"
#include "../actor/castle/MasterCastle.h"
#include "../camera/Camera.h"
#include "../actor/Stage.h"
#include "../actor/Cloud.h"
#include "../actor/enemy/ArmyEnemy.h"
#include "../actor/enemy/VaristorEnemy.h"
#include "../actor/enemy/CannonEnemy.h"
#include "../actor/enemy/ShipEnemy.h"
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
	wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<VaristorEnemy>(wa,Vector3(10,-50,20)));
	wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ShipEnemy>(wa, Vector3(60, -50, 20)));
	//wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ArmyEnemy>(wa, Vector3(40, -50, 30)));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<MonhanCameraActor>(wa));
	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		wa.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wa, Vector3(100.0f * (i - 2), 100.0f, 100.0f * (j - 2))));
	//	}
	//}
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(120,-100,200)));
	//for (int i = 1; i < MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL)); i++)
	//{
	//	if (i % 2 == 0)
	//	{
	//		Vector3 Position = Vector3::ToVECTOR(MV1GetFramePosition(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), i));
	//		boonPositions.push_back(Position);
	//	}
	//}
 //	for (auto i : boonPositions)
	//{
	//	wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, i));
	//}
 // 	int num = MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL));
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
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