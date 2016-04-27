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
#include "../time/Time.h"

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
	wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0, 0, 0), Vector2(5, 12), Vector3(10, 0, 0)));

	Camera::GetInstance().SetRange(0.1f, 3000.0f);
	Camera::GetInstance().Position.Set(Vector3(0.0f,400.0f, -300.0f));
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();
}

float timer = 0.0f;

void TitleScene::Update()
{
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Z)){
		timer += Time::DeltaTime;
	}
	if (timer > 0.05f){
		timer = 0.0f;
		Vector3 pos;
		wa.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
			pos = other.GetParameter().mat.GetPosition();
		});
		//for (int i = 0; i < 2; i++){
		wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<TornadeBillboard>(wa, pos));
		//}
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
	Model::GetInstance().Draw(MODEL_ID::SKY_MODEL, Vector3::Zero, Vector3::Zero, Vector3(5.0f));
	Model::GetInstance().Draw(MODEL_ID::STAGE_MODEL, Vector3::Zero, Vector3::Zero, Vector3(10.0f));
	wa.Draw();

	TextDraw::GetInstance().Draw(Point::Zero, Vector3(255), Vector2(objectcount));
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