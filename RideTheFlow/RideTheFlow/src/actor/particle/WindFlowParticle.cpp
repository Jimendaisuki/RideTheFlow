#include "WindFlowParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"

WindFlowParticle::WindFlowParticle(const std::vector<Vector3>& dashPositions_, float positionHeight_)
:
dashPositions(dashPositions_),
positionHeight(positionHeight_),
rotate(Vector3::Zero)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 0.03f * dashPositions.size();
	lifeParam.isDead = false;

	moveParam.pos = dashPositions.at(0);

	drawParam.drawID = MODEL_ID::WIND_MODEL;
	drawParam.size = 10.0f;
	drawParam.alpha = 0.0f;
	drawParam.blendMode = BLEND_MODE::Alpha;
	drawParam.billboardOrigin = Vector2(0, 0);
}

void WindFlowParticle::OnUpdate()
{
	//�v�f��������Ȃ��ꍇ�͂͂���
	if (dashPositions.size() < 3)
		return;

	//�_�b�V���̋O�Ղ��Ȃ���
	int num = (dashPositions.size() - 1) * (lifeParam.lifeTime / lifeParam.lifeTimeLimit);
	//�͈͊O�֍s���Ȃ��悤�Ɏ~�߂�
	if (num > dashPositions.size() - 1)
		return;
	moveParam.pos = dashPositions.at(num);
	//Y�̒l�͓n����Ă������̂ŌŒ�
	moveParam.pos.y = positionHeight;


	//�A���t�@�l�v�Z
	drawParam.alpha = 1.0f * Math::Sin((lifeParam.lifeTime / lifeParam.lifeTimeLimit) * 180.0f);

	//�ŏ��̂����͌����̌v�Z�����Ȃ�
	if (num < 1)
		return;
	//�i�s����
	Vector3 v = Vector3::Normalize(dashPositions.at(num) - dashPositions.at(num - 1));
	//��]�v�Z
	rotate.y = Math::Degree(Math::Atan2(v.x, v.z));
}

void WindFlowParticle::Draw() const
{
	//Model::GetInstance().Draw2DBlend(drawParam.drawID, moveParam.pos, 0, drawParam.size, drawParam.billboardOrigin, 0, drawParam.blendMode, drawParam.alpha);
	Model::GetInstance().Draw(drawParam.drawID, moveParam.pos, drawParam.alpha, rotate, drawParam.size,true);
}