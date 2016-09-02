#include "PVScene.h"
#include "../AllInclude.h"
#include "../Def.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../sound/Sound.h"
#include "../game/WorkFolder.h"
#include "../math/Math.h"
#include "../time/Time.h"

#include "../UIactor/fadePanel/FadePanel.h"

#define FILE_NAME  "�C��_PV.avi"
#define MOVIE_NAME "�C��_PV"

//�R���X�g���N�^
PVScene::PVScene()
{
}

//�f�X�g���N�^
PVScene::~PVScene()
{
	
}

//�J�n
void PVScene::Initialize()
{
	mIsEnd = false;
	WorkFolder::SetWorkFolder("res/");
	movie.Load(FILE_NAME);
	movie.Seek(MOVIE_NAME, 1.0f);
	movie.Play(MOVIE_NAME);

	/* �t�F�[�h */
	FadePanel::GetInstance().SetInTime(1.0f);
	FadePanel::GetInstance().SetOutTime(1.0f);
}

void PVScene::Update()
{
	/* �C�x���g�J�b�g */
	if ((!FadePanel::GetInstance().IsAction()) &&
		(GamePad::GetInstance().AnyTriggerDown() ||
		 Keyboard::GetInstance().AnyTriggerDown()))
	{
		FadePanel::GetInstance().FadeOut();
	}
	if (!FadePanel::GetInstance().IsAction() &&
		FadePanel::GetInstance().IsFullBlack())
	{
		mIsEnd = true;
		return;
	}

	auto time = movie.IsTime(MOVIE_NAME);
	if (time >= PV_END_TIME && !FadePanel::GetInstance().IsAction())
		FadePanel::GetInstance().FadeOut();
}

//�`��
void PVScene::Draw() const
{
	movie.Draw();
}

//�I�����Ă��邩�H
bool PVScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene PVScene::Next() const
{
	return Scene::Title;
}

void PVScene::End()
{
	wa.Clear();
	movie.Clear();
}
