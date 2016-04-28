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
	////リソース読み込み
	//WorkFolder::SetWorkFolder("res/Model/");
	//Model::GetInstance().Load("Box.x", MODEL_ID::BOX_MODEL);

	timer = 0.0f;
	objectcount = 0;
	mIsEnd = false;
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0, 0, 0), Vector2(5, 12), Vector3(10, 0, 0)));
	wa.Add(ACTOR_ID::SAND_ACTOR, std::make_shared<Sand>(wa));
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


	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z)){
		Vector3 pos;
		wa.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
			pos = other.GetParameter().mat.GetPosition();
		});
		for (int i = 0; i < 20; i++){
		wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<CastleBlock>(wa, pos));
		}
	}
	tornadeTimer += Time::DeltaTime;
	if (tornadeTimer > 0.08f){
		tornadeTimer = 0.0f;
		Vector3 pos;
		wa.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
			pos = other.GetParameter().mat.GetPosition();
		});
		//wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<TornadeBillboard>(wa, pos));
	}

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}
	wa.Update();

	objectcount = 0;
	wa.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		objectcount++;
	});

	Vector3 target;
	wa.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
		target = other.GetParameter().mat.GetPosition();
	});
	Camera::GetInstance().Target.Set(target);
	Camera::GetInstance().Update();
}

//描画
void TitleScene::Draw() const
{
	//Model::GetInstance().Draw(MODEL_ID::SKY_MODEL, Vector3::Zero, Vector3::Zero, Vector3(5.0f));
	//Model::GetInstance().Draw(MODEL_ID::TEST_STAGE, Vector3::Zero, Vector3::Zero, Vector3(0.01f));
	wa.Draw();

	TextDraw::GetInstance().Draw(Vector2(fps));
	//TextDraw::GetInstance().Draw(Point::Zero, Vector3(255), Vector2(objectcount));
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

void TitleScene::End(){
	wa.Clear();
	//リソース全削除
	//Model::GetInstance().DeleteAll();
	//Sprite::GetInstance().DeleteAll();
	//Sound::GetInstance().DeleteAll();
}