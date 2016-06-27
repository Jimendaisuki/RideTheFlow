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
#include "../actor/enemy/DoragonSpearEnemy.h"
#include "../actor/enemy/ShipVaristorEnemy.h"
#include "../actor/island/Froatinglsland.h"
#include "../actor/island/Froatinglsland2.h"
#include "../actor/island/Froatinglsland3.h"
#include "../actor/castle/CastleManager.h"
#include "../UIactor/MiniMap.h"
//火曜日　木曜日
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
	wa.UIAdd(UI_ID::MINIMAP_UI, std::make_shared<MiniMap>(wa));
 	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<MonhanCameraActor>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CastleManager>(wa));

	//MasterCastleの引数は左からworld,position,,Y軸回転,(浮島の上じゃないときはなし、それ以外は浮島のActor),
	//船を出すかどうか,タイトルで使うか　の順

	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(200.0f, 0.0f, 0.0f), 0.0f,
		 true, false));
	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(0.0f, 0.0f, 200.0f), 0.0f,
		true, false));
	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(200.0f, 0.0f, 300.0f), 0.0f,
		true, false));
	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(500.0f, 0.0f, 100.0f), 0.0f,
		true, false));
	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(150.0f, 0.0f, -200.0f), 0.0f,
		true, false));


	//wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland>(wa, Vector3::Zero,1,1));
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
}

void EndhingScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}



	if (wa.GetActorCount(ACTOR_ID::MASTER_CASTLE_ACTOR, ACTOR_ID::MASTER_CASTLE_ACTOR) <= 0 &&
		wa.GetActorCount(ACTOR_ID::SHIP_ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR) <= 0)
	{
		//ゲームクリアー
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