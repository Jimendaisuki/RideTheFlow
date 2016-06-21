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
#include "../actor/island/FloatingIsland.h"
#include "../actor/Stage.h"
#include "../graphic/TextDraw.h"
#include "../actor/castle/MasterCastle.h"

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

static const Vector3 House1Pos = Vector3(-300, -80, 200);

//コンストラクタ
CreditScene::CreditScene():
armyCreateTimer(0.0f)
{
	buttons.clear();

	//mIsEnd = false;
}

//デストラクタ
CreditScene::~CreditScene()
{
}

//開始
void CreditScene::Initialize()
{
	//モデルを一旦解放して読み込み直す
	Model::GetInstance().Delete(MODEL_ID::TEST_MODEL);
	WorkFolder::SetWorkFolder("res/Model/");
	Model::GetInstance().Load("dra_test.mv1", MODEL_ID::TEST_MODEL,false);

	mIsEnd = false;

	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<MonhanCameraActor>(wa));
	//wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ShipEnemy>(wa, Vector3(200, 50, 200)));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<FogActor>(wa));

	wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<BreakCastle>(wa, Vector3(0, 50, -100), CASTLE_SELECT::MASTER_CASTLE));
	//for (int i = 0; i < 2; i++)
	//{
	//	wa.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<Sand>(wa, Vector3(300 * i, -50, 100 * i)));
	//}

	for (int i = 1; i < MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL)); i++)
	{
		if (i % 2 == 0)
		{
			Vector3 Position = Vector3::ToVECTOR(MV1GetFramePosition(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), i));
			boonPositions.push_back(Position);
		}
	}
	for (auto i : boonPositions)
	{
		wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, i,true));
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			wa.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wa, Vector3(100.0f * (i - 2), 100.0f, 100.0f * (j - 2))));
		}
	}

	armyCreateTimer = 0.0f;
	armyCount = 0;
}

void CreditScene::Update()
{
	if (armyCount < 10)
		armyCreateTimer += Time::DeltaTime;
	if (armyCreateTimer > 10.0f)
	{
		armyCreateTimer = 0.0f;
		wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ArmyEnemy>(wa, House1Pos));
		armyCount++;
	}
	

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	wa.Update();

	//入力状態を取得
	//leftstick = GamePad::GetInstance().Stick();
	//rightstick = GamePad::GetInstance().RightStick();
	//buttons.clear();
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM1));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM2));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM3));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM4));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM5));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM7));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM8));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM9));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM10));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM11));
	//buttons.push_back(GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM12));
}

//描画
void CreditScene::Draw() const
{
	//for (int i = 0; i < 10; i++){
	//	for (int j = 0; j < 10; j++){
	//		Model::GetInstance().Draw(MODEL_ID::CANNON_MODEL, Vector3(100 + i * 20, -80, 100 + j * 20), Vector3::Zero, Vector3(0.9f));
	//		Model::GetInstance().Draw(MODEL_ID::BALLISTA_MODEL, Vector3(-200 + i * 30, -80, 200 + j * 30), Vector3::Zero, Vector3(0.9f));
	//		Model::GetInstance().Draw(MODEL_ID::HOME_MODEL, Vector3(-500 + i * 100, -80, -500 + j * 100), Vector3::Zero, Vector3(0.9f));
	//	}
	//}
	//Model::GetInstance().Draw(MODEL_ID::ISLE_1_MODEL, Vector3(700, 200, -500), Vector3::Zero, Vector3(1));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_2_MODEL, Vector3(400, 200, -500), Vector3::Zero, Vector3(1));
	//Model::GetInstance().Draw(MODEL_ID::ISLE_3_MODEL, Vector3(100, 200, -500), Vector3::Zero, Vector3(1));
	//Model::GetInstance().Draw(MODEL_ID::SHIP_MODEL, Vector3(300, 200, 500), Vector3::Zero, Vector3(0.4f));
	
	Model::GetInstance().Draw(MODEL_ID::HOME_MODEL, House1Pos , Vector3::Zero, Vector3(1.0f));

	Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_1_MODEL, Vector3(100,200, 100), Vector3::Zero, Vector3(30.0f));
	Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_2_MODEL, Vector3(200,200, 200), Vector3::Zero, Vector3(30.0f));
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_3_MODEL, Vector3(300,200, 300), Vector3::Zero, Vector3(30.0f));
	Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_4_MODEL, Vector3(400,200, 400), Vector3::Zero, Vector3(30.0f));
	Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_5_MODEL, Vector3(500,200, 500), Vector3::Zero, Vector3(30.0f));
	Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_6_MODEL, Vector3(600,200, 600), Vector3::Zero, Vector3(30.0f));
	//Model::GetInstance().Draw(MODEL_ID::CASTLE_BREAK_7_MODEL, Vector3(700,200, 700), Vector3::Zero, Vector3(30.0f));


	wa.Draw();
	
	////スティックの入力状態
	//int drawx = 700;
	//TextDraw::Draw(Point(drawx, 180), Vector3::Blue, "Sticks");
	//TextDraw::Draw(Point(drawx, 200), Vector3::Blue, leftstick);
	//TextDraw::Draw(Point(drawx, 220), Vector3::Blue, rightstick);
	////ボタンの入力状態
	//TextDraw::Draw(Point(drawx, 260), Vector3::Green, "Buttons");
	//for (int i = 0; i < 12; i++)
	//{
	//	TextDraw::Draw(Point(drawx, 280 + 20 * i), Vector3::Green, Vector2(buttons.at(i)));
	//}

	////ステージの限界の大きさのワイヤー球
	//DrawSphere3D(Vector3::Zero.ToVECTOR(), 1400, 10, GetColor(0, 125, 125), GetColor(0, 125, 125), 0);
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