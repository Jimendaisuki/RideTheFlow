#include "GamePlayScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../math/Vector2.h"
#include "../input/Keyboard.h"
#include "../input/GamePad.h"
#include "../game/Random.h"
#include "../game/WorkFolder.h"

#include "../actor/Player.h"
#include "../actor/MonhanCameraActor.h"
#include "../actor/Stage.h"
#include "../actor/StageGenerator.h"
#include "../actor/castle/CastleManager.h"
#include "../actor/Cloud.h"
#include "../CloudSetting.h"
#include "../actor/FogActor.h"
#include "../UIactor/MiniMap.h"


//コンストラクタ
GamePlayScene::GamePlayScene()
{
}

//デストラクタ
GamePlayScene::~GamePlayScene()
{
}

//開始
void GamePlayScene::Initialize()
{
	mIsEnd = false;

	//モデルを一旦解放して読み込み直す
	Model::GetInstance().Delete(MODEL_ID::TEST_MODEL);
	WorkFolder::SetWorkFolder("res/Model/");
	Model::GetInstance().Load("dra_test.mv1", MODEL_ID::TEST_MODEL, false);

	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<MonhanCameraActor>(wa));
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	wa.Add(ACTOR_ID::BEGIN_ACTOR,  std::make_shared<CastleManager>(wa));
	wa.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<StageGenerator>(wa, "TitleStage"));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<FogActor>(wa));
	wa.UIAdd(UI_ID::MINIMAP_UI, std::make_shared<MiniMap>(wa));

	for (int i = 0; i < CLOUD_LOW_POSITION_NUM; i++)
		wa.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wa, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 0.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));
	for (int i = 0; i < CLOUD_HIGH_POSITION_NUM; i++)
		wa.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wa, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 1400.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));

	menu.Initialize();
}

void GamePlayScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::E)){
		mIsEnd = true;
	}

	/* メニュー系統 */
	menu.Update();
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE) ||
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM9))
		menu.Action();
	if (menu.IsAction())
		return;

	wa.Update();
}

//描画
void GamePlayScene::Draw() const
{
	wa.Draw();
	menu.Draw();
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

void GamePlayScene::End()
{
	wa.Clear();
}