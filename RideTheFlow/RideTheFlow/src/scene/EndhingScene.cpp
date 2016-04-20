#include"EndhingScene.h"
#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include "../actor/CameraActor.h"
#include "../actor/EnemyBullet.h"
#include "../actor/Player.h"
#include "../actor/tornado/Tornado.h"
#include "../actor/EnemyGun.h"


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
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	
	//wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0, 0, 0), Vector3(10, 0, 0)));
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(Vector3(0.0f,0.0f,-80.0f));
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);

}

void EndhingScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}
	timeTest++;
	if (timeTest%100==0)
	wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<EnemyGun>(wa));

	wa.Update();
	Camera::GetInstance().Update();
}

//描画
void EndhingScene::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::TORNADO_MODEL, Vector3(15.0f, 15.0f, 15.0f));
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