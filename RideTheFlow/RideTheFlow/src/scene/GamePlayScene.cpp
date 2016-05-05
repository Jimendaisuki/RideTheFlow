#include "GamePlayScene.h"
#include "../AllInclude.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/Player.h"
#include "../actor/CameraActor.h"

#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include "../actor/tornado/Tornado.h"
#include "../actor/Stage.h"
#include "../actor/castle/MasterCastle.h"


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
	boonPositions.clear();
	mIsEnd = false;
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));

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
//	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(wa));
	
	//wa.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wa, Vector3(0, 0, 0), Vector3(10, 0, 0)));
}

void GamePlayScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
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
	return Scene::Ending;
}

void GamePlayScene::End(){
	boonPositions.clear();
	wa.Clear();
}