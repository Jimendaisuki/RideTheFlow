#include"EndhingScene.h"
#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include"../actor/SpringCameraActor.h"
#include "../actor/CameraActor.h"
#include "../actor/EnemyBullet.h"
#include "../actor/Player.h"
#include "../actor/tornado/Tornado.h"
#include "../actor/EnemyGun.h"
#include "../actor/EnemyGunBullet.h"
#include"../actor/Enemy.h"
#include "../actor/EnemyVaristor.h"
#include "../actor/EnemyParachuteBomb.h"
#include "../actor/castle/MasterCastle.h"
//コンストラクタ
EndhingScene::EndhingScene()
{
	timeTest = 0;
	//mIsEnd = false;
	position = Vector3::Zero;
	boonPositions.clear();
}

//デストラクタ
EndhingScene::~EndhingScene()
{
}

//開始
void EndhingScene::Initialize()
{
	//position = Vector3::ToVECTOR(MV1GetFramePosition(Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE), 1)) ;
	//position /= 100.0f;
	mIsEnd = false;
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<SpringCameraActor>(wa));

	for (int i = 0; i < MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE)); i++)
	{
		position = Vector3::ToVECTOR(MV1GetFramePosition(Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE), i));
		position /= 100;
		boonPositions.push_back(position);
	}
	for (auto i : boonPositions)
	{
		wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, i, Vector3(0, 0, 0), Vector3::One));
	}
	int num = MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE));
	/*wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3::Zero, Vector3(0, 0, 0), Vector3::One));*/
	//wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<EnemyGun>(wa, Vector3(40.0f, 0.0f, 0.0f)));
	//wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<Enemy>(wa, Vector3(20.0f, 0.0f, 0.0f)));
	//wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<EnemyVaristor>(wa, Vector3(0.0f, 0.0f, 0.0f)));
	//wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<EnemyParachiteBomb>(wa, Vector3(-20.0f, 0.0f, 0.0f)));

	//wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0, 0, 0), Vector3(10, 0, 0)));
}

void EndhingScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}
	
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::G))
	{
		/*wa.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyGunBullet>(wa, Vector3(15.0f, 15.0f, 0.0f)));*/
		//wa.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(wa, Vector3(0,0,0), 30.0f));
	}
	Camera::GetInstance().Update();
	wa.Update();
}

//描画
void EndhingScene::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::TEST_STAGE, Vector3::Zero, Vector3::Zero, Vector3(0.01f));
	//Model::GetInstance().Draw(MODEL_ID::SKY_MODEL, Vector3::Zero, Vector3::Zero, Vector3(5.0f));
	DrawFormatString(0, 300, GetColor(255, 255, 255), "boonPosition    %f %f %f", position.x, position.y, position.z);

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
	position = Vector3::Zero;
	wa.Clear();
}