#include "CreditScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/CameraActor.h"

#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include "../actor/tornado/Tornado.h"
#include "../actor/castle/Castle.h"


//�R���X�g���N�^
CreditScene::CreditScene()
{

	//mIsEnd = false;
}

//�f�X�g���N�^
CreditScene::~CreditScene()
{
}

//�J�n
void CreditScene::Initialize()
{
	mIsEnd = false;
	//wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));

	wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0, 0, 0), Vector3(10, 0, 0)));
	wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(0, 0, 0), Vector3(20, 20, 20)));
	wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(20, 10, 0), Vector3(10, 10, 10)));
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(-50, 50, 0)));
	//wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(wa, Vector3(50, 50, 100)));
}

void CreditScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	wa.Update();
}

//�`��
void CreditScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "CreditScene");
	wa.Draw();
}

//�I�����Ă��邩�H
bool CreditScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene CreditScene::Next() const
{
	return Scene::Title;
}

void CreditScene::End(){
	wa.Clear();
}