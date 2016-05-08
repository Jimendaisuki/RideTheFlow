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

#include "../actor/Effect.h"
#include "../actor/Stage.h"
#include "../actor/TitleCameraActor.h"
#include "../time/Time.h"

#include "../actor/CameraActor.h"

//コンストラクタ
TitleScene::TitleScene()
{

}

//デストラクタ
TitleScene::~TitleScene()
{

}

int	  modelHandle = 0;
float frameCount = 0;
float frameNum = 0;

//開始
void TitleScene::Initialize()
{
	timer = 0.0f;
	objectcount = 0;
	mIsEnd = false;
	//wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	//wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<TitleCameraActor>(wa));
	
	modelHandle = Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL);
	frameCount = MV1GetFrameNum(modelHandle);

	position = Vector3::Zero;

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(Vector3(0, 500, -200));
	Camera::GetInstance().Target.Set(position);
	Camera::GetInstance().Up.Set(Vector3::Up);
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

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)) position.x--;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)) position.x++;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) position.y++;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) position.y--;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::E)) position.z--;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Q)) position.z++;


	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP)) frameNum++;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN)) frameNum--;
	if (frameNum > frameCount - 1) frameNum = 0;
	if (frameNum < 0) frameNum = frameCount - 1;


	/* 集中線発生 */
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LSHIFT))
		Effect::GetInstance().DashEffect(wa, position);

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	wa.Update();

	Camera::GetInstance().Position.Set(Vector3(0, 100, -200));
	Camera::GetInstance().Target.Set(Vector3(0, 100, 0));
	Camera::GetInstance().Update();
}

//描画
void TitleScene::Draw() const
{
	wa.Draw();

	DrawSphere3D(position, 2, 4, GetColor(255, 0, 0), GetColor(0, 0, 0), true);

	TextDraw::GetInstance().Draw("TitleScene");
	DrawFormatString(0, 20, GetColor(255, 255, 255), "FPS:		%f", fps);

	DrawFormatString(0, 100, GetColor(255, 0, 0), "LSHIFT	: ダッシュ演出");

	DrawFormatString(0, 150, GetColor(0, 0, 0), "FrameNum  : %f", frameNum);
	DrawFormatString(0, 170, GetColor(0, 0, 0), "FrameName : %s", MV1GetFrameName(modelHandle, frameNum));
	Vector3 position = Vector3::ToVECTOR(MV1GetFramePosition(modelHandle, frameNum));
	DrawFormatString(0, 190, GetColor(0, 0, 0), "FramePos  : [%f] [%f] [%f]", position.x, position.y, position.z);
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