#include "TitleCameraActor.h"
#include "Collision.h"
#include "../Def.h"
#include "../camera/Camera.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../math/Math.h"
#include "../time/Time.h"
#include "../world/IWorld.h"
#include "../game/Random.h"
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
	std::random_shuffle(roots.begin(), roots.end());
	maxRootCount = roots.size();

	Camera::GetInstance().SetRange(0.1f, 40000.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();
}

TitleCameraActor::~TitleCameraActor()
{
	roots.clear();
	useRoots.clear();
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
			rootCount %= maxRootCount;
			GetRoot(rootCount);
			rootCount++;
		}

		backAlpha -= Time::DeltaTime * 5.0f;

		if (time + 0.1f <= useRoots.front().moveTime)
		{
			float nowTime = time / useRoots.front().moveTime;
			float targetTime = nowTime + 0.1f;

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
				if (useRoots.size() == 1)
				{
					cameraPos = BeziersCurve4(bez.Get(CBezier::eNoAccel, CBezier::eNoAccel, nowTime), useRoots.front().points);
					targetPos = BeziersCurve4(bez.Get(CBezier::eNoAccel, CBezier::eNoAccel, targetTime), useRoots.front().points);
				}
				else
				{
					cameraPos = BeziersCurve4(nowTime, useRoots.front().points);
					targetPos = BeziersCurve4(targetTime, useRoots.front().points);
				}

				break;
			default:
				useRoots.clear();
				break;
			}
		}
		else
		{
			velocity = cameraPos - prePos;
			time = 0.0f;
			useRoots.pop_front();
			if (useRoots.size() == 0)
				fade = !fade;
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
}

void TitleCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

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

void TitleCameraActor::RootLoad()
{
	while (currentRow_ < csv_.rows())
	{
		AddRootList();
	}
}

const int CSV_POINT_NUM = 0;
const int CSV_MOVE_TIME = 1;
const int CSV_POSITOIN  = 2;
const int CSV_OFFSET	= 5;
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
		root.points[i] = position * Vector3(2.3f, 1.5f, 2.3f) + Vector3(0.0f, 250.0f, 0.0f);
		currentRow_++;
	}
	// �ۑ�
	roots.push_back(root);
}

void TitleCameraActor::GetRoot(int num)
{
	useRoots.clear();

	Vector3 p1, p2, centerPos, vecA, vecB;
	float length = 0.0f, lenA = 0.0f, lenB = 0.0f;

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
		for (int i = 1; i < 6; i++)
		{
			Vector3 v = rootData.points[i] - rootData.points[i - 1];
			length += v.Length();
		}
		//vecA = centerPos - rootData.points[0];
		//vecB = rootData.points[5] - centerPos;
		//lenA = vecA.Length();
		//lenB = vecB.Length();
		//length = lenA + lenB;

		/* ���[�gA */
		// ���W�̕ۑ�
		for (int i = 0; i < 3; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.points[3] = centerPos;
		// ���Ԃ̎Z�o
		for (int i = 1; i < 4; i++)
		{
			lenA += (root.points[i] - root.points[i - 1]).Length();
		}
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
		for (int i = 1; i < 4; i++)
		{
			lenB += (root.points[i] - root.points[i - 1]).Length();
		}
		root.moveTime = rootData.moveTime * (lenB / length);

		// ���[�gB�ۑ�
		useRoots.push_back(root);
		break;
	default:
		useRoots.clear();
		break;
	}
}