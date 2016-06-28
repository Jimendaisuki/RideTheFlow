#include "MenuScene.h"
#include "../UIactor/fadePanel/FadePanel.h"
#include "../UIactor/menuPanel/MenuPanel.h"
#include "../actor/Stage.h"
#include "../actor/StageGenerator.h"
#include "../input/Keyboard.h"
#include "../camera/Camera.h"
#include "../sound/Sound.h"

//�R���X�g���N�^
MenuScene::MenuScene()
{

}

//�f�X�g���N�^
MenuScene::~MenuScene()
{

}

//�J�n
void MenuScene::Initialize()
{
	mIsEnd = false;
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<StageGenerator>(wo, "TitleStage", false));
	status = MENU_STATUS::BEGIN;

	MenuPanel::GetInstance().Initialize();

	/* �J�����ݒ� */
	Camera::GetInstance().SetRange(0.1f, 40000.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Position.Set(Vector3(2225.0f, -312.0f, 4587.0f));
	Camera::GetInstance().Target.Set(Vector3(0.0f, 1840.0f, -15264.0f));
	Camera::GetInstance().Update();

	Vector3 lightPos = Camera::GetInstance().Position.Get().Normalized() * 10000;
	lightPos.y = 30000.0f;
	SetLightPosition(lightPos);
	SetLightDirection(-lightPos.Normalized());

	Sound::GetInstance().PlayBGM(BGM_ID::MENU_BGM);

	/* �t�F�[�h */
	FadePanel::GetInstance().SetInTime(1.0f);
}

void MenuScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
	}

	if (!Sound::GetInstance().IsPlayBGM())
		Sound::GetInstance().PlayBGM(BGM_ID::MENU_BGM);


	switch (status)
	{
	case BEGIN:
		if (FadePanel::GetInstance().IsFullClear() && !MenuPanel::GetInstance().IsAction())
		{
			MenuPanel::GetInstance().Action(Scene::Menu);
			status = MENU_STATUS::STANBAY;
		}
		break;
	case STANBAY:
		if (MenuPanel::GetInstance().IsEnd())
		{
			FadePanel::GetInstance().FadeOut(1.0f);
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

	MenuPanel::GetInstance().Update();
}

//�`��
void MenuScene::Draw() const
{
	wo.Draw();
	MenuPanel::GetInstance().Draw();
}

//�I�����Ă��邩�H
bool MenuScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene MenuScene::Next() const
{
	if (MenuPanel::GetInstance().IsBackSelect()) return Scene::Title;
	else return Scene::Event;
}

void MenuScene::End()
{
	wo.Clear();
	Sound::GetInstance().StopBGM();
}

