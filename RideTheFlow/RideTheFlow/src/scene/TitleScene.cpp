#include "TitleScene.h"
#include "../AllInclude.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../sound/Sound.h"
#include "../input/Keyboard.h"
#include "../game/Random.h"
#include "../graphic/TextDraw.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/AnimTestActor.h"
#include "../actor/CameraActor.h"
#include "../actor/castle/CastleBlock.h"
#include "../actor/tornado/TornadeBillboard.h"
#include "../actor/tornado/Tornado.h"
#include "../actor/Sand.h"
#include "../time/Time.h"
#include "../actor/Stage.h"

#include "../actor/Effect.h"

//コンストラクタ
TitleScene::TitleScene()
{

}

//デストラクタ
TitleScene::~TitleScene()
{

}

//開始
void TitleScene::Initialize()
{
	timer = 0.0f;
	objectcount = 0;
	mIsEnd = false;
	//wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	Camera::GetInstance().SetRange(0.1f, 3000.0f);
	Camera::GetInstance().Position.Set(Vector3(0.0f,400.0f, -300.0f));
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();
}

float tornadeTimer = 0.0f;
float fpsTimer = 0.0f;
float fps;

void TitleScene::Update()
{
	fpsTimer += Time::DeltaTime;
	if (fpsTimer > 1.0f)
	{
		fps = 1.0f / Time::DeltaTime;
		fpsTimer = 0.0f;
	}
	
	/* 集中線発生 */
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LSHIFT))
		Effect::GetInstance().DashEffect(wa);

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}
	wa.Update();

	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Update();
}

//描画
void TitleScene::Draw() const
{
	wa.Draw();

	TextDraw::GetInstance().Draw("TitleScene");
	DrawFormatString(0, 20, GetColor(255, 255, 255), "FPS:		%f", fps);

	DrawFormatString(0, 100, GetColor(255, 255, 255), "LSHIFT	: ダッシュ演出");
}

//終了しているか？
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene TitleScene::Next() const
{
	return Scene::GamePlay;
}

void TitleScene::End()
{
	wa.Clear();
}