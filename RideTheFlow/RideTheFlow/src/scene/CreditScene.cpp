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

#include "../actor/particle/ParticleSystem.h"

//コンストラクタ
CreditScene::CreditScene()
{

	//mIsEnd = false;
}

//デストラクタ
CreditScene::~CreditScene()
{
}

//開始
void CreditScene::Initialize()
{
	mIsEnd = false;
	//wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));

	//wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(50, 0, 0), Vector2(1, 1), Vector3::Zero));
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 1.0f, 1.0f));
	//wa.Add(ACTOR_ID::ISLAND_ACTOR, std::make_shared<FroatingIsland>(wa, Vector3(0, 20, 0), Vector3(0, 0, 0), Vector3(1, 1, 1)));

	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	//ParticleSystem(wa, MODEL_ID::SMOKE_2D, 0.1f, 100, 1000.0f, Vector3(0), true, 200.0f, 30.0f, 255.0f, Vector2::Zero, 0.0f, 0.0f, -120.0f,BLEND_MODE::Alpha);
	//ParticleSystem(wa, MODEL_ID::WIND_2D, 0.01f, 1, 1000.0f, 4.0f,
	//	Vector3(0, 100, 0), Vector3::One, Vector3(10, 100, 10),
	//	400.0f, 30.0f, 255.0f, Vector2::Zero, 0.0f, 0.0f, -70.0f, BLEND_MODE::Alpha);
	//wa.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<ParticleSystem>(
	//	wa, MODEL_ID::WIND_2D, 0.02f, 1, 1000.0f, 4.0f,
	//	Vector3(200, 100, 0), Vector3(-1,0,0), Vector3(1, 100, 100),
	//	80.0f, 30.0f, 255.0f, Vector2::Zero, 0.0f, 0.0f, -70.0f, BLEND_MODE::Alpha));

	Camera::GetInstance().SetRange(0.1f, 3000.0f);
	Camera::GetInstance().Position.Set(Vector3(0.0f, 300.0f, -300.0f));
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();

	MV1SetupCollInfo(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), -1, 32, 8, 32);
}

void CreditScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	wa.Update();
}

//描画
void CreditScene::Draw() const
{
	//Model::GetInstance().Draw(MODEL_ID::STAGE_MODEL, Vector3::Zero, Vector3::Zero, Vector3(10.0f));

	//MV1_REF_POLYGONLIST RefPory;
	//RefPory = MV1GetReferenceMesh(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL), -1, false);
	//
	//DrawCube3D(RefPory.MinPosition, RefPory.MaxPosition, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
	//Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, Vector3::Zero, Vector3::Zero, true);

	//DrawFormatString(10, 10, GetColor(255, 255, 255), "CreditScene");
	//DrawFormatString(10, 30, GetColor(255, 255, 255), "FPS   %d", (int)(1.0f / Time::DeltaTime));

	wa.Draw();
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