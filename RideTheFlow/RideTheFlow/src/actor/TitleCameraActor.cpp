#include "TitleCameraActor.h"
#include "Collision.h"
#include "../Def.h"
#include "../camera/Camera.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../math/Math.h"
#include "../time/Time.h"
#include "../world/IWorld.h"
#include <list>
#include <algorithm>

TitleCameraActor::TitleCameraActor(IWorld& world) :
Actor(world),
time(0.0f),
backAlpha(0.0f),
fade(false),
rootCount(0),
maxRootCount(0)
{
	parameter.id = ACTOR_ID::CAMERA_ACTOR;
	parameter.isDead = false;

	currentRow_ = 0;
	csv_.load("res/root.csv");

	roots.clear();
	useRoots.clear();

	RootLoad();
	random_shuffle(roots.begin(), roots.end());
	maxRootCount = roots.size();

	Camera::GetInstance().SetRange(0.1f, 20000.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();
}

TitleCameraActor::~TitleCameraActor()
{
	Clear();
}
void TitleCameraActor::Update()
{
	if (fade)
	{
		backAlpha += Time::DeltaTime * 5.0f;
		cameraPos += velocity;
		targetPos += velocity;

		if (backAlpha >= 1.0f)
			fade = !fade;
	}
	else
	{
		// ���[�g���擾
		if (useRoots.size() == 0)
		{
			rootCount++;
			int rootNum = (rootCount % maxRootCount);
			GetRoot(rootNum);
		}

		backAlpha -= Time::DeltaTime * 5.0f;

		if (time + 0.1f <= useRoots.front().moveTime)
		{
			float nowTime = time / useRoots.front().moveTime;
			float targetTime = nowTime + 0.5f;

			switch (useRoots.front().moveNum)
			{
			case 2:
				cameraPos = Lerp(nowTime, useRoots.front().points);
				targetPos = Lerp(targetTime, useRoots.front().points);
				break;
			case 3:
				cameraPos = BeziersCurve3(nowTime, useRoots.front().points);
				targetPos = BeziersCurve3(targetTime, useRoots.front().points);
				break;
			case 4:
				cameraPos = BeziersCurve4(nowTime, useRoots.front().points);
				targetPos = BeziersCurve4(targetTime, useRoots.front().points);
				break;
			default:
				useRoots.clear();
				break;
			}
		}
		else
		{
			velocity = cameraPos - prePos;
			fade = !fade;
			time = 0.0f;
			useRoots.pop_front();
		}

		time += Time::DeltaTime;
	}

	prePos = cameraPos;
	backAlpha = Math::Clamp(backAlpha, 0.0f, 1.0f);

	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();
}
void TitleCameraActor::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::BLACK_SCREEN, Vector2::Zero, Vector2::Zero, backAlpha, Vector2(WINDOW_WIDTH / 800.0f, WINDOW_HEIGHT / 600.0f), 0.0f, false, false);
	//DrawFormatString(0, 340, GetColor(0, 0, 255), "CameraPos  : [%f] [%f] [%f]", cameraPos.x, cameraPos.y, cameraPos.z);
	//DrawFormatString(0, 360, GetColor(0, 0, 255), "TargetPos  : [%f] [%f] [%f]", targetPos.x, targetPos.y, targetPos.z);
}

void TitleCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}

// �x�W�G�ړ�
void TitleCameraActor::BeziersCurve(float sec)
{
	float b = time / sec;
	float a = 1.0f - b;

	/* �ʒu�Z�o */
	//p.x = a*a*a*frames[0].x + 3 * a*a*b*frames[1].x + 3 * a*b*b*frames[2].x + b*b*b*frames[3].x;
	//p.y = a*a*a*frames[0].y + 3 * a*a*b*frames[1].y + 3 * a*b*b*frames[2].y + b*b*b*frames[3].y;
	//p.z = a*a*a*frames[0].z + 3 * a*a*b*frames[1].z + 3 * a*b*b*frames[2].z + b*b*b*frames[3].z;

	Vector3 p = Vector3::Zero;

	/* �J�����E�^�[�Q�b�g�ʒu�X�V */
	targetPos = Vector3(p.x, p.y, p.z);
	cameraPos = targetPos - (targetPos - prePos).Normalized() * 50.0f;

	// �O�t���[���ۑ�
	prePos = targetPos;

	if (time >= sec) time = 0;
}

// ���`���
Vector3 TitleCameraActor::Lerp(float sec, Vector3 points[2])
{
	Vector3 result;
	result = Vector3::Lerp(points[0], points[1], sec);

	return result;
}

// �x�W�G�ړ�
Vector3 TitleCameraActor::BeziersCurve3(float sec, Vector3 points[3])
{
	float b = sec;
	float a = 1.0f - b;

	/* �ʒu�Z�o */
	Vector3 result;
	result.x = a*a*points[0].x + 2 * a*b*points[1].x + b*b*points[2].x;
	result.y = a*a*points[0].y + 2 * a*b*points[1].y + b*b*points[2].y;
	result.z = a*a*points[0].z + 2 * a*b*points[1].z + b*b*points[2].z;

	return result;
}

// �x�W�G�ړ�
Vector3 TitleCameraActor::BeziersCurve4(float sec, Vector3 points[4])
{
	float b = sec;
	float a = 1.0f - b;

	/* �ʒu�Z�o */
	Vector3 result;
	result.x = a*a*a*points[0].x + 3 * a*a*b*points[1].x + 3 * a*b*b*points[2].x + b*b*b*points[3].x;
	result.y = a*a*a*points[0].y + 3 * a*a*b*points[1].y + 3 * a*b*b*points[2].y + b*b*b*points[3].y;
	result.z = a*a*a*points[0].z + 3 * a*a*b*points[1].z + 3 * a*b*b*points[2].z + b*b*b*points[3].z;

	return result;
}

void TitleCameraActor::Clear()
{
	//roots.clear();
	useRoots.clear();
}

void TitleCameraActor::RootLoad()
{
	while (currentRow_ < csv_.rows())
	{
		AddRootList();
	}
}

const int CSV_POINT_NUM = 0;
const int CSV_MOVE_TIME = 1;
const int CSV_OFFSET    = 2;
const int CSV_POSITOIN  = 5;
void TitleCameraActor::AddRootList()
{
	RootData root;
	// ���_���擾
	root.pointNum = csv_.getf(currentRow_, CSV_POINT_NUM);
	// ���Ԏ擾
	root.moveTime = csv_.getf(currentRow_, CSV_MOVE_TIME);
	// �I�t�Z�b�g�擾
	const Vector3 offset(
		csv_.getf(currentRow_, CSV_OFFSET + 0),
		csv_.getf(currentRow_, CSV_OFFSET + 0),
		csv_.getf(currentRow_, CSV_OFFSET + 0));
	// ���W�擾
	for (int i = 0; i < root.pointNum; i++)
	{
		const Vector3 position(
			csv_.getf(currentRow_, CSV_POSITOIN + 0),
			csv_.getf(currentRow_, CSV_POSITOIN + 1),
			csv_.getf(currentRow_, CSV_POSITOIN + 2));
		root.points[i] = position;
		currentRow_++;
	}
	// �ۑ�
	roots.push_back(root);
}

void TitleCameraActor::GetRoot(int num)
{
	useRoots.clear();

	Vector3 p1, p2, centerPos, vecA, vecB;
	float length, lenA, lenB;

	// �ۑ����ꂽ���[�g�f�[�^
	RootData rootData = roots[num];
	// ���ꂩ��g�����[�g�f�[�^
	SetRoot  root;

	switch (rootData.pointNum)
	{
	case 2:
		for (int i = 0; i < 2; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.moveNum  = rootData.pointNum;
		root.moveTime = rootData.moveTime;
		// �ۑ�
		useRoots.push_back(root);
		break;
	case 3:
		for (int i = 0; i < 3; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.moveNum  = rootData.pointNum;
		root.moveTime = rootData.moveTime;
		// �ۑ�
		useRoots.push_back(root);
		break;
	case 4:
		for (int i = 0; i < 4; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.moveNum  = rootData.pointNum;
		root.moveTime = rootData.moveTime;
		// �ۑ�
		useRoots.push_back(root);
		break;
	case 6:
		// ���_��
		root.moveNum = 4;

		// ���ԓ_
		p1 = rootData.points[2];
		p2 = rootData.points[3];
		centerPos = p1 + (p2 - p1) / 2.0f;

		// �������Z�o
		vecA = centerPos - rootData.points[0];
		vecB = rootData.points[5] - centerPos;
		lenA = vecA.Length();
		lenB = vecB.Length();
		length = lenA + lenB;

		/* ���[�gA */
		// ���W�̕ۑ�
		for (int i = 0; i < 3; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.points[3] = centerPos;
		// ���Ԃ̎Z�o
		root.moveTime = rootData.moveTime * (lenA / length);

		// ���[�gA�ۑ�
		useRoots.push_back(root);

		/* ���[�gB */
		// ���W�̕ۑ�
		root.points[0] = centerPos;
		for (int i = 1; i < 4; i++)
		{
			root.points[i] = rootData.points[i + 2];
		}
		// ���Ԃ̎Z�o
		root.moveTime = rootData.moveTime * (lenB / length);

		// ���[�gB�ۑ�
		useRoots.push_back(root);
		break;
	default:
		useRoots.clear();
		break;
	}
}