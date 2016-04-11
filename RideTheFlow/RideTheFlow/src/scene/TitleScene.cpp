#include "TitleScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/Enemy.h"


//�R���X�g���N�^
TitleScene::TitleScene()
{
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
}

//�J�n
void TitleScene::Initialize()
{
	mIsEnd = false;
	wa.Add(ACTOR_ID::ENEMY, std::make_shared<Enemy>());
}

void TitleScene::Update()
{
	if (CheckHitKeyAll()){
		mIsEnd = true;
	}
	wa.Update();
}

//�`��
void TitleScene::Draw() const
{
	wa.Draw();
}

//�I�����Ă��邩�H
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene TitleScene::Next() const
{
	return Scene::GamePlay;
}

void TitleScene::End(){
	wa.Clear();
}