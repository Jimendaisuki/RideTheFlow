#include"EndhingScene.h"
#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include"../actor/SpringCameraActor.h"
#include "../actor/Player.h"
#include "../actor/castle/MasterCastle.h"
#include "../camera/Camera.h"
#include "../actor/Stage.h"
//�R���X�g���N�^
EndhingScene::EndhingScene()
{
	timeTest = 0;
	//mIsEnd = false;
	position = Vector3::Zero;
}

//�f�X�g���N�^
EndhingScene::~EndhingScene()
{
}

//�J�n
void EndhingScene::Initialize()
{
	boonPositions.clear();
	mIsEnd = false;
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<SpringCameraActor>(wa));

	for (int i = 1; i < MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL)); i++)
	{
		if (i % 2 == 0)
		{
			Vector3 Position = Vector3::ToVECTOR(MV1GetFramePosition(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL), i));
			boonPositions.push_back(Position);
		}
	}
 	for (auto i : boonPositions)
	{
		wa.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, i));
	}
  	int num = MV1GetFrameNum(Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL));
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
}

void EndhingScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}

	Camera::GetInstance().Update();
	wa.Update();
}

//�`��
void EndhingScene::Draw() const
{
	wa.Draw();
}

//�I�����Ă��邩�H
bool EndhingScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene EndhingScene::Next() const
{
	return Scene::Credit;
}

void EndhingScene::End(){
	boonPositions.clear();
	wa.Clear();
}