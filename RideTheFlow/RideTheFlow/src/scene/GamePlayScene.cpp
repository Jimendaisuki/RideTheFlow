#include "GamePlayScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"

#include "../math/Vector2.h"
#include "../camera/Camera.h"

//�R���X�g���N�^
GamePlayScene::GamePlayScene()
{

	//mIsEnd = false;
}

//�f�X�g���N�^
GamePlayScene::~GamePlayScene()
{
}

//�J�n
void GamePlayScene::Initialize()
{
	mIsEnd = false;
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
}

void GamePlayScene::Update()
{
	Camera::GetInstance().Update();

	if (CheckHitKeyAll()){
		mIsEnd = true;
	}
	wa.Update();
}

//�`��
void GamePlayScene::Draw() const
{
	wa.Draw();
}

//�I�����Ă��邩�H
bool GamePlayScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene GamePlayScene::Next() const
{
	return Scene::Title;
}

void GamePlayScene::End(){
	wa.Clear();
}