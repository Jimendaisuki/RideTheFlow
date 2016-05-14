#include "TitleCameraActor.h"
#include "Collision.h"
#include "../camera/Camera.h"
#include "../graphic/Model.h"
#include "../time/Time.h"
#include "../world/IWorld.h"

/* ���� 
Draw�����ł�����-100����Ă��邽�߁A
2��ڈȍ~��bone�̈ʒu��-100����Ă���͗l
�ǂ����Ń��Z�b�g
*/

TitleCameraActor::TitleCameraActor(IWorld& world) :
Actor(world),
time(0.0f)
{
	parameter.id = ACTOR_ID::CAMERA_ACTOR;
	parameter.isDead = false;

	stageModelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE);

	parentFrames.clear();
	for (int i = 1; i < MV1GetFrameNum(stageModelHandle); i++)
	{
		if (MV1GetFrameParent(stageModelHandle, i) == -2)
			parentFrames.push_back(i);
	}

	SetFrame(0);

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();
}

TitleCameraActor::~TitleCameraActor()
{
	frames.clear();
}
void TitleCameraActor::Update()
{
	time += Time::DeltaTime;

	switch (frames.size())
	{
	case 2:
		Liner(2.0f);
		break;
	case 4:
		BeziersCurve(2.0f);
		break;
	default:
		SetFrame(0);
		break;
	}

	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();
}
void TitleCameraActor::Draw() const
{
	DrawFormatString(0, 300, GetColor(0, 0, 255), "StartPos   : [%f] [%f] [%f]", startPos.x, startPos.y, startPos.z);
	DrawFormatString(0, 320, GetColor(0, 0, 255), "EndPos	  : [%f] [%f] [%f]", endPos.x, endPos.y, endPos.z);
	DrawFormatString(0, 340, GetColor(0, 0, 255), "CameraPos  : [%f] [%f] [%f]", cameraPos.x, cameraPos.y, cameraPos.z);
	DrawFormatString(0, 360, GetColor(0, 0, 255), "TargetPos  : [%f] [%f] [%f]", targetPos.x, targetPos.y, targetPos.z);
}

void TitleCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}

// �J�����t���[���Z�b�g
void TitleCameraActor::SetFrame(int num)
{
	/* ������ */
	frames.clear();
	/* ������� */
	int frameChildCount = 1;
	int child = MV1GetFrameChildNum(stageModelHandle, parentFrames[num]);
	frames.push_back(Vector3::ToVECTOR(MV1GetFramePosition(stageModelHandle, parentFrames[num])));
	
	/* ���[�g�t���[����ۑ� */
	while (child >= 0)
	{
		frames.push_back(Vector3::ToVECTOR(MV1GetFramePosition(stageModelHandle, parentFrames[num] + frameChildCount)));
		frameChildCount++;
		child = MV1GetFrameParent(stageModelHandle, parentFrames[0] + frameChildCount);
	}

	/* �����ʒu */
	prePos = frames[0];
}

// �����ړ�
void TitleCameraActor::Liner(float sec)
{
	//targetPos = Vector3::Lerp(startPos, endPos, time / sec);
	//cameraPos = targetPos - ((endPos - startPos) * Vector3(1.0f, 0.0f, 1.0f)).Normalized() * 10.0f;
	targetPos = Vector3::Lerp(frames[0], frames[1], time / sec);
	cameraPos = targetPos - ((frames[1] - frames[0]) * Vector3(1.0f, 0.0f, 1.0f)).Normalized() * 10.0f;

	if (time >= sec) time = 0;
}

// �x�W�G�ړ�
void TitleCameraActor::BeziersCurve(float sec)
{
	float b = time / sec;
	float a = 1 - b;

	/* �ʒu�Z�o */
	p.x = a * a * a * frames[0].x + 3 * a*a*b*frames[1].x + 3 * a*b*b*frames[2].x + b*b*b*frames[3].x;
	p.y = a * a * a * frames[0].y + 3 * a*a*b*frames[1].y + 3 * a*b*b*frames[2].y + b*b*b*frames[3].y;
	p.z = a * a * a * frames[0].z + 3 * a*a*b*frames[1].z + 3 * a*b*b*frames[2].z + b*b*b*frames[3].z;

	/* �J�����E�^�[�Q�b�g�ʒu�X�V */
	targetPos = Vector3(p.x, p.y, p.z);
	cameraPos = targetPos - (targetPos - prePos).Normalized() * 50.0f;

	/* �O�t���[���ۑ� */
	prePos = p;

	if (time >= sec) time = 0;
}