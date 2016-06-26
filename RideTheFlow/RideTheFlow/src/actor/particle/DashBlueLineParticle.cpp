#include "DashBlueLineParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"

DashBlueLineParticle::DashBlueLineParticle( const std::vector<Vector3>& dashPositions_, float positionHeight_)
:
dashPositions(dashPositions_),
randomPosition(Random::GetInstance().Range(-10.0f, 10.0f), 0.0f, Random::GetInstance().Range(-10.0f, 10.0f)),
positionHeight(positionHeight_),
rotate(Vector3::Zero)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 0.03f * dashPositions.size();
	lifeParam.isDead = false;

	moveParam.pos = dashPositions.at(0);

	drawParam.drawID = MODEL_ID::WIND_BLUE_MODEL;
	drawParam.size = 15.0f;
	drawParam.alpha = 1.0f;
	drawParam.blendMode = BLEND_MODE::Alpha;
	drawParam.billboardOrigin = Vector2(0, 0);
}

void DashBlueLineParticle::OnUpdate()
{
	int size = dashPositions.size();

	//�v�f��������Ȃ��ꍇ�͂͂���
	if (size < 3)
		return;

	//�_�b�V���̋O�Ղ��Ȃ���
	int num = size - (size * (lifeParam.lifeTime / lifeParam.lifeTimeLimit));
	//�͈͊O�֍s���Ȃ��悤�Ɏ~�߂�
	if (num > size - 1 || num < 0)
		return;

	//�\��������W���v�Z�@�_�b�V���̋O�Ղ��烉���_���Ȓl�����炷
	moveParam.pos = dashPositions.at(num) + randomPosition;
	//Y�̒l�͓n����Ă������̂ŌŒ�
	moveParam.pos.y = positionHeight;

	//�A���t�@�l�v�Z
	drawParam.alpha = 1.0f * Math::Cos((lifeParam.lifeTime / lifeParam.lifeTimeLimit) * 90.0f);

	//�ŏ��̂����͌����̌v�Z�����Ȃ�
	if (num < 1)
		return;
	//�i�s����
	Vector3 v = Vector3::Normalize(dashPositions.at(num) - dashPositions.at(num - 1));
	//��]�v�Z
	rotate.y = Math::Degree(Math::Atan2(v.x, v.z));

}

void DashBlueLineParticle::Draw() const
{
	Model::GetInstance().Draw(drawParam.drawID, moveParam.pos, drawParam.alpha, rotate, drawParam.size, true);
}
