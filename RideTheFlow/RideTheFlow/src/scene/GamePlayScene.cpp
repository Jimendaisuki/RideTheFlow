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
#include "../math/Math.h"
#include "../time/Time.h"
#include "../sound/Sound.h"
#include "../camera/Camera.h"

#include "../actor/Player.h"
#include "../actor/MonhanCameraActor.h"
#include "../actor/Stage.h"
#include "../actor/StageGenerator.h"
#include "../actor/castle/CastleManager.h"
#include "../actor/Cloud.h"
#include "../CloudSetting.h"
#include "../actor/FogActor.h"
#include "../UIactor/MiniMap.h"
#include "../UIactor/Failure.h"


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
	isGameEnd = false;
	isPlayerDead = false;

	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa, false, false, Vector3(0.0f, 0.0f, -5500.0f), Vector3(0,0,1)));
	wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0.0f, 0.0f, -5500.0f), Vector2(100), Vector3::Zero, 100.0f));
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
	FadePanel::GetInstance().SetInTime(2.0f);
	bgmVol = 1.0f;
	Sound::GetInstance().SetBGMVolume(BGM_ID::INGAME_BGM, bgmVol);
}

void GamePlayScene::Update()
{
	/* サウンド */
	if (!Sound::GetInstance().IsPlayBGM() && !isGameEnd)
		Sound::GetInstance().PlayBGM(BGM_ID::INGAME_BGM, DX_PLAYTYPE_LOOP);

	if (isGameEnd && FadePanel::GetInstance().IsFullBlack())
	{
		mIsEnd = true;
		return;
	}

	/* メニュー更新 */
	menu.Update();
	if (menu.IsAction())
		return;

	wa.Update();

	// 終了してたら以下省略
	if (isGameEnd)
	{
		bgmVol -= Time::DeltaTime;
		bgmVol = Math::Clamp(bgmVol, 0.0f, 1.0f);
		Sound::GetInstance().SetBGMVolume(BGM_ID::INGAME_BGM, bgmVol);
		return;
	}

	if (menu.IsBackSelect())
	{
		isGameEnd = true;
		FadePanel::GetInstance().SetOutTime(0.5f);
		FadePanel::GetInstance().FadeOut();
		return;
	}


	/* ポーズ表示 */
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE) ||
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM9))
	{
		menu.Action();
	}

	/* クリア判定 */
	if (wa.GetActorCount(ACTOR_ID::MASTER_CASTLE_ACTOR, ACTOR_ID::MASTER_CASTLE_ACTOR) <= 0 &&
		wa.GetActorCount(ACTOR_ID::SHIP_ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR) <= 0)
	{
		isGameEnd = true;
		FadePanel::GetInstance().SetOutTime(0.5f);
		FadePanel::GetInstance().FadeOut();
	}

	/* プレイヤー死亡判定 */
	if (wa.GetPlayer()->GetParameter().HP <= 0.0f)
	{
		isGameEnd = true;
		isPlayerDead = true;
		wa.UIAdd(UI_ID::FAILERE_UI, std::make_shared<Failure>(wa));
		Sound::GetInstance().StopBGM();
		Sound::GetInstance().PlayBGM(BGM_ID::FAILED_BGM);
	}
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
	if (menu.IsBackSelect())
		return Scene::Menu;
	else if (isPlayerDead)
		return Scene::Title;
	else
		return Scene::Ending;
}

void GamePlayScene::End()
{
	wa.Clear();
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().SetAllBGMVolume(1.0f);
	Sound::GetInstance().SetAllSEVolume(1.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
}