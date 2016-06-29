#include "MenuScene.h"
#include "../UIactor/fadePanel/FadePanel.h"
#include "../UIactor/menuPanel/MenuPanel.h"
#include "../actor/Stage.h"
#include "../actor/StageGenerator.h"
#include "../input/Keyboard.h"
#include "../camera/Camera.h"
#include "../sound/Sound.h"

//コンストラクタ
MenuScene::MenuScene()
{

}

//デストラクタ
MenuScene::~MenuScene()
{

}

//開始
void MenuScene::Initialize()
{
	mIsEnd = false;
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<StageGenerator>(wo, "TitleStage", false));
	status = MENU_STATUS::BEGIN;

	menu.Initialize();

	/* カメラ設定 */
	Camera::GetInstance().SetRange(0.1f, 40000.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Position.Set(Vector3(2225.0f, -312.0f, 4587.0f));
	Camera::GetInstance().Target.Set(Vector3(0.0f, 1840.0f, -15264.0f));
	Camera::GetInstance().Update();

	Vector3 lightPos = Camera::GetInstance().Position.Get().Normalized() * 10000;
	lightPos.y = 30000.0f;
	SetLightPosition(lightPos);
	SetLightDirection(-lightPos.Normalized());

	/* 音 */
	Sound::GetInstance().PlayBGM(BGM_ID::MENU_BGM, DX_PLAYTYPE_LOOP);

	/* フェード */
	FadePanel::GetInstance().SetInTime(2.0f);
	FadePanel::GetInstance().SetOutTime(2.0f);
}

void MenuScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
	}

	switch (status)
	{
	case BEGIN:
		if (FadePanel::GetInstance().IsFullClear() && !menu.IsAction())
		{
			menu.Action();
			status = MENU_STATUS::STANBAY;
		}
		break;
	case STANBAY:
		if (menu.IsEnd())
		{
			FadePanel::GetInstance().FadeOut();
			status = MENU_STATUS::END;
		}
		break;
	case END:
		if (FadePanel::GetInstance().IsFullBlack())
			mIsEnd = true;
		break;
	default:
		break;
	}

	menu.Update();
}

//描画
void MenuScene::Draw() const
{
	wo.Draw();
	menu.Draw();
}

//終了しているか？
bool MenuScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene MenuScene::Next() const
{
	if (menu.IsBackSelect()) return Scene::Title;
	else return Scene::Event;
}

void MenuScene::End()
{
	wo.Clear();
	Sound::GetInstance().StopBGM();
}

