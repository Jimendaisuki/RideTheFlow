#include"EndhingScene.h"
#include "../math/Math.h"
#include "../math/Vector2.h"
#include "../time/Time.h"
#include "../input/Keyboard.h"
#include "../input/GamePad.h"
#include "../actor/Player.h"
#include "../actor/Stage.h"
#include "../actor/Cloud.h"
#include "../camera/Camera.h"
#include "../UIactor/fadePanel/FadePanel.h"
#include "../UIactor/Clear.h"

float const LENGTH = 10000.0f;
float const HEIGHT = 10000.0f;

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
	float x = Math::Sin(angle) * LENGTH;
	float z = Math::Cos(angle) * LENGTH;
	cameraPos = Vector3(x, HEIGHT, z);
	targetPos = Vector3::Up * 1000.0f;

	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().SetRange(0.1f, 40000.0f);
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();


	FadePanel::GetInstance().SetInTime(0.5f);
	FadePanel::GetInstance().SetOutTime(2.0f);
}

void EndhingScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	angle += Time::DeltaTime * 10.0;
	float x = Math::Sin(angle) * LENGTH;
	float z = Math::Cos(angle) * LENGTH;
	cameraPos = Vector3(x, HEIGHT, z);
	targetPos = Vector3::Up * 2000.0f;

	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
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