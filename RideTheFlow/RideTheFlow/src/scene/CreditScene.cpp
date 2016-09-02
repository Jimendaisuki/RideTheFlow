#include "CreditScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/CameraActor.h"

#include "../input/Keyboard.h"
#include "../time/Time.h"

#include "../actor/tornado/Tornado.h"
#include "../actor/castle/Castle.h"
#include "../actor/island/Froatinglsland.h"
#include "../actor/Stage.h"
#include "../graphic/TextDraw.h"
#include "../actor/castle/MasterCastle.h"
#include "../game/Random.h"
#include "../actor/MonhanCameraActor.h"
#include "../game/WorkFolder.h"
#include "../actor/Cloud.h"
#include "../actor/castle/CastleBlock.h"
#include "../actor/particle/Sand.h"
#include "../actor/enemy/ShipEnemy.h"
#include "../actor/enemy/ArmyEnemy.h"
#include "../input/GamePad.h"
#include "../actor/FogActor.h"
#include "../actor/particle/BreakCastle.h"
#include "../actor/tornado/Tornado.h"
#include "../UIactor/MiniMap.h"
#include "../actor/particle/CastleAdd.h"
#include "../graphic/Anime.h"
#include "../sound/Sound.h"
#include "../actor/castle/HomeActor.h"
#include "../actor/StageGenerator.h"
#include "../CloudSetting.h"
#include "../actor/castle/CastleManager.h"
#include "../WindAndTornadoSetting.h"

static const Vector3 House1Pos = Vector3(0, -680, 0);

//コンストラクタ
CreditScene::CreditScene():
armyCreateTimer(0.0f)
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
	//wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	//wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	//wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<MonhanCameraActor>(wa));
	//wa.Add(ACTOR_ID::BEGIN_ACTOR, std::make_shared<CastleManager>(wa));
	////wa.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<StageGenerator>(wa, "TitleStage"));
	//wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	//wa.UIAdd(UI_ID::MINIMAP_UI, std::make_shared<MiniMap>(wa));
	//wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<FogActor>(wa));
	//for (int i = 0; i < CLOUD_LOW_POSITION_NUM; i++)
	//{
	//	wa.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wa, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 0.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));
	//}
	//for (int i = 0; i < CLOUD_HIGH_POSITION_NUM; i++)
	//{
	//	wa.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wa, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 1400.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));
	//}


	////============================テスト用======================================
	//wa.Add(ACTOR_ID::SAND_ACTOR, std::make_shared<Sand>(wa,Vector3(0,-700,0), Vector3::Forward));

	//wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(0, -600, 0), 1.0f, 0.0f, true, false,0));

	//wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	//wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<MonhanCameraActor>(wa));
	//wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<FogActor>(wa));
	//wa.UIAdd(UI_ID::MINIMAP_UI, std::make_shared<MiniMap>(wa));

	//wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<HomeActor>(wa, 1.0f, Vector3::Zero, Vector3(0, 170, 0)));

	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<BreakCastle>(wa, Vector3(-200, 0, -100), CASTLE_SELECT::SHIP, BREAK_SELECT::TORNADO));
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<BreakCastle>(wa, Vector3(0, 0, -100),    CASTLE_SELECT::SHIP, BREAK_SELECT::WIND_FLOW));
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<BreakCastle>(wa, Vector3(200, 0, -100),  CASTLE_SELECT::SHIP, BREAK_SELECT::WIND_BALL));

	//float bai = 8.0;
	//wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(700, -80, 0)	 * bai, 0.0f, true, false));
	//wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(100, -80, 0)	 * bai, 0.0f, true, false));
	//wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(-30, -80, 300)	 * bai, 0.0f, true, false));
	//wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(20,  -80, -400)	 * bai, 0.0f, true, false));
	//wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(300, -80, 700)	 * bai, 0.0f, true, false));

	armyCreateTimer = 0.0f;
	armyCount = 0;

	//Sound::GetInstance().PlayBGM(BGM_ID::INGAME_BGM);
}

void CreditScene::Update()
{
	//if (armyCount < 10)
	//	armyCreateTimer += Time::DeltaTime;
	//if (armyCreateTimer > 10.0f)
	//{
	//	armyCreateTimer = 0.0f;
	//	wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ArmyEnemy>(wa, House1Pos));
	//	armyCount++;
	//}
	
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	wa.Update();

	//入力状態を取得
	leftstick = GamePad::GetInstance().Stick();
	rightstick = GamePad::GetInstance().RightStick();
	buttons.clear();
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM1));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM2));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM3));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM4));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM5));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM7));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM8));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM9));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM10));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM11));
	buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM12));
}

//描画
void CreditScene::Draw() const
{
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_1_MODEL, Vector3(100,200, 100), Vector3::Zero, Vector3(30.0f));
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_2_MODEL, Vector3(200,200, 200), Vector3::Zero, Vector3(30.0f));
	////Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_3_MODEL, Vector3(300,200, 300), Vector3::Zero, Vector3(30.0f));
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_4_MODEL, Vector3(400,200, 400), Vector3::Zero, Vector3(30.0f));
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_5_MODEL, Vector3(500,200, 500), Vector3::Zero, Vector3(30.0f));
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_6_MODEL, Vector3(600,200, 600), Vector3::Zero, Vector3(30.0f));
	////Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_7_MODEL, Vector3(700,200, 700), Vector3::Zero, Vector3(30.0f));

	//Matrix4 m;
	//m = Matrix4::Scale(30.0f) * Matrix4::Translate(Vector3(100, 200, 100));
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_MASTER_MODEL, m);

	Model::GetInstance().Draw(MODEL_ID::HOME_MODEL, House1Pos, Vector3::Zero, Vector3(1.0f));

	//Anime::GetInstance().AttachAnime(MODEL_ID::HUMAN_ARCHER_MODEL, 0);
	//Anime::GetInstance().PlayAnime(MODEL_ID::HUMAN_ARCHER_MODEL, 0, t);

	//Model::GetInstance().Draw(MODEL_ID::CASTLE_ADD_MODEL, Vector3(0, 0, -100),1.0f, Vector3::Zero, Vector3(0.05f), diffuse, specu);
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_ADD_MODEL, Vector3(0, 0, -100), Vector3::Zero, Vector3(0.1f));

	Model::GetInstance().Draw(MODEL_ID::ISLE_1_MODEL, Vector3(500, 100, 800), Vector3::Zero, Vector3(8.0f));

	Model::GetInstance().Draw(MODEL_ID::ISLE_1_BREAK_1_MODEL, Vector3(0,  -100,   800) + Vector3(0,1000,0), Vector3::Zero, Vector3(8.0f));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_1_BREAK_3_MODEL, Vector3(0,  -100,   800) + Vector3(0,200,0), Vector3::Zero, Vector3(8.0f));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_1_BREAK_4_MODEL, Vector3(0,  -100,   800) + Vector3(0,200,0), Vector3::Zero, Vector3(8.0f));
																		  		
	//Model::GetInstance().Draw(MODEL_ID::ISLE_2_BREAK_1_MODEL, Vector3(1000,100, -300), Vector3::Zero, Vector3(4.8f));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_2_BREAK_2_MODEL, Vector3(1000,100, -300), Vector3::Zero, Vector3(4.8f));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_2_BREAK_3_MODEL, Vector3(1000,100, -300), Vector3::Zero, Vector3(4.8f));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_2_BREAK_4_MODEL, Vector3(1000,100, -300), Vector3::Zero, Vector3(4.8f));
	//																	  		
	//Model::GetInstance().Draw(MODEL_ID::ISLE_3_BREAK_1_MODEL, Vector3(2000,100, -300), Vector3::Zero, Vector3(4.8f));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_3_BREAK_2_MODEL, Vector3(2000,100, -300), Vector3::Zero, Vector3(4.8f));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_3_BREAK_3_MODEL, Vector3(2000,100, -300), Vector3::Zero, Vector3(4.8f));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_3_BREAK_4_MODEL, Vector3(2000,100, -300), Vector3::Zero, Vector3(4.8f));

	wa.Draw();

	//TextDraw::Draw(Point(900, 180), Vector3::Blue, Vector2(t));

	//スティックの入力状態
	int drawx = 1000;
	TextDraw::Draw(Point(drawx, 180), Vector3::Blue, "Sticks");
	TextDraw::Draw(Point(drawx, 200), Vector3::Blue, leftstick);
	TextDraw::Draw(Point(drawx, 220), Vector3::Blue, rightstick);
	//ボタンの入力状態
	TextDraw::Draw(Point(drawx, 260), Vector3::Green, "Buttons");
	for (int i = 0; i < 12; i++)
	{
		TextDraw::Draw(Point(drawx, 280 + 20 * i), Vector3::Green, Vector2(buttons.at(i)));
	}

	//ステージの限界の大きさのワイヤー球
	////DrawSphere3D(Vector3::Zero.ToVECTOR(), 6000, 10, GetColor(0, 125, 125), GetColor(0, 125, 125), 0);
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
Scene CreditScene::GetCurrentScene() const
{
	return Scene::Credit;
}

void CreditScene::End(){
	wa.Clear();
}