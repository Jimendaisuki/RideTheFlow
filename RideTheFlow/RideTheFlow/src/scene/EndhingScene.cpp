#include"EndhingScene.h"
#include "../math/Vector2.h"
#include "../input/Keyboard.h"

#include"../actor/MonhanCameraActor.h"
#include "../actor/Player.h"
#include "../actor/castle/MasterCastle.h"
#include "../camera/Camera.h"
#include "../actor/Stage.h"
#include "../actor/Cloud.h"
#include "../actor/enemy/ArmyEnemy.h"
#include "../actor/enemy/VaristorEnemy.h"
#include "../actor/enemy/CannonEnemy.h"
#include "../actor/enemy/ShipEnemy.h"
#include "../actor/enemy/DoragonSpearEnemy.h"
#include "../actor/enemy/ShipVaristorEnemy.h"
#include "../actor/island/Froatinglsland.h"
#include "../actor/island/Froatinglsland2.h"
#include "../actor/island/Froatinglsland3.h"
#include "../actor/castle/CastleManager.h"
#include "../UIactor/MiniMap.h"
//�Ηj���@�ؗj��
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
	wa.UIAdd(UI_ID::MINIMAP_UI, std::make_shared<MiniMap>(wa));
 	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<MonhanCameraActor>(wa));
	wa.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CastleManager>(wa));

	//MasterCastle�̈����͍�����world,position,,Y����],(�����̏ザ��Ȃ��Ƃ��͂Ȃ��A����ȊO�͕�����Actor),
	//�D���o�����ǂ���,�^�C�g���Ŏg�����@�̏�

	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(200.0f, 0.0f, 0.0f), 0.0f,
		 true, false));
	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(0.0f, 0.0f, 200.0f), 0.0f,
		true, false));
	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(200.0f, 0.0f, 300.0f), 0.0f,
		true, false));
	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(500.0f, 0.0f, 100.0f), 0.0f,
		true, false));
	wa.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(wa, Vector3(150.0f, 0.0f, -200.0f), 0.0f,
		true, false));


	//wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland>(wa, Vector3::Zero,1,1));
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
}

void EndhingScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)){
		mIsEnd = true;
	}



	if (wa.GetActorCount(ACTOR_ID::MASTER_CASTLE_ACTOR, ACTOR_ID::MASTER_CASTLE_ACTOR) <= 0 &&
		wa.GetActorCount(ACTOR_ID::SHIP_ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR) <= 0)
	{
		//�Q�[���N���A�[
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