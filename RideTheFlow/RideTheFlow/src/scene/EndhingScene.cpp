#include"EndhingScene.h"
#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include "../actor/MonhanCameraActor.h"
#include "../actor/Player.h"
#include "../actor/Stage.h"
#include "../actor/Cloud.h"
#include "../camera/Camera.h"

float const LENGTH = 10000.0f;

//コンストラクタ
EndhingScene::EndhingScene()
{
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
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));

	angle = 0.0f;
}

void EndhingScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}



	if (wa.GetActorCount(ACTOR_ID::MASTER_CASTLE_ACTOR, ACTOR_ID::MASTER_CASTLE_ACTOR) <= 0 &&
		wa.GetActorCount(ACTOR_ID::SHIP_ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR) <= 0)
	{
		//mIsEnd = true;
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
	return Scene::Title;
}

void EndhingScene::End()
{
	wa.Clear();
}