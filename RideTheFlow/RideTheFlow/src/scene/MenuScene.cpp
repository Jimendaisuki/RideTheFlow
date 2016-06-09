#include "MenuScene.h"
#include "../UIactor/fadePanel/FadePanel.h"
#include "../UIactor/menuPanel/MenuPanel.h"
#include "../actor/Stage.h"
#include "../input/Keyboard.h"

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
	status = MENU_STATUS::BEGIN;

	MenuPanel::GetInstance().Initialize();

	/* �t�F�[�h */
	FadePanel::GetInstance().Initialize();
	FadePanel::GetInstance().FadeIn(1.0f);
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
		if (FadePanel::GetInstance().IsFullClear() && !MenuPanel::GetInstance().IsAction())
		{
			MenuPanel::GetInstance().Action(Scene::Menu);
			status = MENU_STATUS::STANBAY;
		}
		break;
	case STANBAY:
		if (MenuPanel::GetInstance().IsEnd())
		{
			FadePanel::GetInstance().FadeOut(2.0f);
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
	FadePanel::GetInstance().Update();
}

//�`��
void MenuScene::Draw() const
{
	wo.Draw();

	MenuPanel::GetInstance().Draw();
	FadePanel::GetInstance().Draw();
	DrawFormatString(0, 0, GetColor(255, 255, 255), "MenuScene");
	DrawFormatString(0, 240, GetColor(255, 0, 0), "N		: ��");
	DrawFormatString(0, 260, GetColor(255, 0, 0), "B		: �~");
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
	else return Scene::GamePlay;
}

void MenuScene::End()
{
	wo.Clear();
}

