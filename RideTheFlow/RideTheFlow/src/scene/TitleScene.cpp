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
#include "../actor/tornado/Tornado.h"

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
	////���\�[�X�ǂݍ���
	//WorkFolder::SetWorkFolder("res/Model/");
	//Model::GetInstance().Load("Box.x", MODEL_ID::BOX_MODEL);

	mIsEnd = false;
	wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0,-30,0), Vector3::Right));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));
}

void TitleScene::Update()
{
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Z)){
		Vector3 pos;
		wa.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
			pos = other.GetParameter().mat.GetPosition();
		});
		wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<CastleBlock>(wa, pos, Random::GetInstance().Range(8.0f, 10.0f)));
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
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
	//���\�[�X�S�폜
	//Model::GetInstance().DeleteAll();
	//Sprite::GetInstance().DeleteAll();
	//Sound::GetInstance().DeleteAll();
}