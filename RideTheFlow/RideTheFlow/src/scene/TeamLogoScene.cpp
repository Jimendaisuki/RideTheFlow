#include "TeamLogoScene.h"
#include "../AllInclude.h"
#include "Scene.h"
#include "../input/Keyboard.h"
#include "../graphic/Sprite.h"
#include "../Def.h"

//�R���X�g���N�^
TeamLogoScene::TeamLogoScene()
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
	mIsEnd = true;
	wa.Update();
}

//�`��
void TeamLogoScene::Draw() const
{
	wa.Draw();
	Sprite::GetInstance().Draw(SPRITE_ID::LOADING_SPRITE, Vector2(WINDOW_WIDTH - 700.0f, WINDOW_HEIGHT - 125.0f));
}

//�I�����Ă��邩�H
bool TeamLogoScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene TeamLogoScene::Next() const
{
	return Scene::Ending;
}

void TeamLogoScene::End(){
	wa.Clear();
}