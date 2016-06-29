#include "TeamLogoScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/AnimTestActor.h"
#include "../actor/CameraActor.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"

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

void TeamLogoScene::End(){
	wa.Clear();
}