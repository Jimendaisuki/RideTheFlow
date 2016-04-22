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
//コンストラクタ
EndhingScene::EndhingScene()
{
	timeTest = 0;
	//mIsEnd = false;
}

//デストラクタ
EndhingScene::~EndhingScene()
{
}

//開始
void EndhingScene::Initialize()
{
	mIsEnd = false;
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<SpringCameraActor>(wa));
	

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
		wa.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(wa, Vector3(0,0,0), 30.0f));
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
	wa.Clear();
}