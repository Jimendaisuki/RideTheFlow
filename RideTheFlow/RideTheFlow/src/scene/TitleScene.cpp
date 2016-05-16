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

#include "../UIactor/Effect.h"
#include "../actor/Stage.h"
#include "../actor/TitleCameraActor.h"
#include "../time/Time.h"

#include "../actor/CameraActor.h"
#include "../math/Math.h"
#include "../UIactor/Damege.h"

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
float frameParentCount = 0;
float frameChildCount = 0;

//開始
void TitleScene::Initialize()
{
	timer = 0.0f;
	objectcount = 0;
	mIsEnd = false;
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	//wo.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<TitleCameraActor>(wo));
	
	modelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE);
	frameCount = MV1GetFrameNum(modelHandle);
	frameParentCount = MV1GetFrameParent(modelHandle, frameNum);
	frameChildCount = MV1GetFrameChildNum(modelHandle, frameNum);

	position = Vector3::Zero;

	wo.UIAdd(EFFECT_ID::SPEED_EFFECT, std::make_shared<Damege>(wo));


	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(Vector3(0, 500, -200));
	Camera::GetInstance().Target.Set(position);
	Camera::GetInstance().Up.Set(Vector3::Up);
}

float tornadeTimer = 0.0f;
float fpsTimer = 0.0f;
float fps;

int effectNum = 0.0f;

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
	frameParentCount = MV1GetFrameParent(modelHandle, frameNum);
	frameChildCount = MV1GetFrameChildNum(modelHandle, frameNum);

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z)) effectNum++;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::X)) effectNum--;
	effectNum = Math::Clamp(effectNum, 0, 4);

	/* スピード線発生 */
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LSHIFT))
		switch (effectNum)
		{
			case 1: 
				Effect::GetInstance().StepEffect(wo, EffectDirection::Up);
				break;
			case 2: 
				Effect::GetInstance().StepEffect(wo, EffectDirection::Down);
				break;
			case 3:
				Effect::GetInstance().StepEffect(wo, EffectDirection::Left);
				break;
			case 4:
				Effect::GetInstance().StepEffect(wo, EffectDirection::Right);
				break;
			default:
				Effect::GetInstance().DashEffect(wo, position);
				break;
		}
		
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::C)){
		Effect::GetInstance().DamegeEffect(wo, position);
	}

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	wo.Update();

	Camera::GetInstance().Position.Set(Vector3(0, 100, -200));
	Camera::GetInstance().Target.Set(Vector3(0, 100, 0));
	Camera::GetInstance().Update();
}

//描画
void TitleScene::Draw() const
{
	wo.Draw();

	DrawSphere3D(position, 2, 4, GetColor(255, 0, 0), GetColor(0, 0, 0), true);

	TextDraw::GetInstance().Draw("TitleScene");
	DrawFormatString(0, 20, GetColor(255, 255, 255), "FPS:		%f", fps);

	DrawFormatString(0, 100, GetColor(255, 0, 0), "LSHIFT	: スピード線演出");
	DrawFormatString(0, 120, GetColor(255, 0, 0), "Z,X		: 演出切り替え");

	DrawFormatString(0, 150, GetColor(0, 0, 0), "FrameNum  : %f", frameNum);
	DrawFormatString(0, 170, GetColor(0, 0, 0), "FrameName : %s", MV1GetFrameName(modelHandle, frameNum));
	DrawFormatString(0, 190, GetColor(0, 0, 0), "FramePare : %f", frameParentCount);
	DrawFormatString(0, 210, GetColor(0, 0, 0), "FrameChild: %f", frameChildCount);
	Vector3 position = Vector3::ToVECTOR(MV1GetFramePosition(modelHandle, frameNum));
	DrawFormatString(0, 230, GetColor(0, 0, 0), "FramePos  : [%f] [%f] [%f]", position.x, position.y, position.z);
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
	wo.Clear();
}