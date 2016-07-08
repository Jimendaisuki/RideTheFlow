#include "VaristorEnemy.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
#include "EnemyParameter.h"
#include "../../time/Time.h"
#include "VaristorBullet.h"
#include "../../math/Math.h"
#include "../Player.h"
#include "../../math/Quaternion.h"

VaristorEnemy::VaristorEnemy(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
playerDot(0),
mPosition(position),
rotate(Vector3::Zero),
isLook(true)
{
	parameter.HP = 7.0f;

	parameter.isDead = false;
	parameter.mat = Matrix4::Translate(mPosition);
	parameter.radius = 10.0f;

}
VaristorEnemy::~VaristorEnemy()
{

}
void VaristorEnemy::Update()
{
	TackleParameter tp;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});
	//�����蔻��
	////world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR , COL_ID::TORNADO_ENEMY_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::ENEMY_WIND_COL);
	//�v���C���[�̑O
	Vector3 playerFront = playerMat.GetFront().Normalized()*cameraFrontAttack + playerMat.GetPosition();
	//�G�ƃv���C���[�̊p�x�����߂�
	float playerAngle = atan2(playerMat.GetPosition().y - mPosition.y,
		Math::Sqrt(Math::Pow(playerMat.GetPosition().z - mPosition.z, 2) +
		Math::Pow(playerMat.GetPosition().x - mPosition.x, 2))) *
		180 / 3.1415f;
	//�G�����U���̊p�x
	float attackAngleZ = atan2(playerFront.y - mPosition.y,
		Math::Sqrt(Math::Pow(playerFront.z - mPosition.z, 2) +
		Math::Pow(playerFront.x - mPosition.x, 2))) *
		180 / 3.1415f;

	//�v���C���[�������Ă��邩�ǂ���
	if (isLook)
	{
		mArrowNumber = VaristorArrorwNum;
		mSecondAttack = VaristorAttackTime;
	}
	else
	{
		mArrowNumber = NotLookVaristorArrowNum;
		mSecondAttack = NotLookVaristorAttackTime;
	}
	isLook = true;
	//�_�b�V�����ȊO�̓v���C���[�̑O�ɖ�����
	if (tp.dashFlag)
	{
		playerDot = Vector3::Dot(parameter.mat.GetLeft(), playerMat.GetPosition());
		attackAngleZ = playerAngle;
	}
	else
	{
		playerDot = Vector3::Dot(parameter.mat.GetLeft(), playerFront*cameraFrontAttack);
	}

	//�E�ɂ��邩���ɂ��邩���m���ߐ��񂷂�
	if (Math::Abs(playerDot) >= 2.0f)
	{
		if (playerDot > 0)
		{
			rotate.y += ConnonSwingSpeed*Time::DeltaTime;
		}
		else
		{
			rotate.y -= ConnonSwingSpeed*Time::DeltaTime;
		}
	}
	//�U��
	attackRag += Time::DeltaTime;
	attackTime += Time::DeltaTime;
	if (attackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= VaristorRange &&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f&&
		playerAngle <= VaristorAttackMaxAngle&&playerAngle >= VaristorAttackMinAngle)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<VaristorBullet>(world, mPosition, *this, rotate.y-90,attackAngleZ,VaristorInitialVelocity));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	//�}�g���b�N�X�v�Z
	parameter.mat =
		Quaternion::RotateAxis(Vector3::Up, rotate.y) *
		Matrix4::Translate(mPosition);
}
void VaristorEnemy::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::BALLISTA_MODEL, parameter.mat.GetPosition(), rotate - Vector3(0, 90, 0));
}
void VaristorEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::TORNADO_ENEMY_COL)
	{
		parameter.isDead = true;
	}
	if (colpara.colID == COL_ID::ENEMY_WIND_COL&&colpara.colFlag)
	{
		parameter.isDead = true;
	}
}