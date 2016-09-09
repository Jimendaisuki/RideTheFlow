#include "TeamLogoScene.h"
#include "../AllInclude.h"
#include "Scene.h"
#include "../input/Keyboard.h"
#include "../graphic/Sprite.h"
#include "../Def.h"

//�R���X�g���N�^
TeamLogoScene::TeamLogoScene() :
count(0)
{
}

//�f�X�g���N�^
TeamLogoScene::~TeamLogoScene()
{
}

//�J�n
void TeamLogoScene::Initialize()
{
	mIsEnd = false;
}

void TeamLogoScene::Update()
{
	if (count >= 1)
		mIsEnd = true;
	else
		count++;
	//wa.Update();
}

//�`��
void TeamLogoScene::Draw() const
{
	//wa.Draw();
	//Sprite::GetInstance().Draw(SPRITE_ID::LOADING_SPRITE, Vector2(WINDOW_WIDTH - 700.0f, WINDOW_HEIGHT - 125.0f));

	int handle = LoadGraph("res/Sprite/nowloading.png");

	DrawRotaGraph3((int)WINDOW_WIDTH - 700.0f, (int)WINDOW_HEIGHT - 125.0f, 0, 0,
		1.0f, 1.0f, 0.0, handle, true, false);
}

//�I�����Ă��邩�H
bool TeamLogoScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene TeamLogoScene::Next() const
{
	return Scene::Title;
}
Scene TeamLogoScene::GetCurrentScene() const
{
	return Scene::Logo;
}

void TeamLogoScene::End(){
	wa.Clear();
}