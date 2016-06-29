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
	useRoots_C.clear();


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
	useRoots_C.clear();
}

void TitleCameraActor::Update()
{
	if (fade)
	{
		backAlpha += Time::DeltaTime * 3.0f;
		cameraPos += velocity;
		targetPos += velocity;

		if (backAlpha >= 1.0f)
			fade = !fade;
	}
	else
	{
		// ルートを取得
		if (useRoots_C.size() == 0)
		{
			rootCount %= maxRootCount;
			GetRoot(rootCount);
			rootCount++;

			Vector3 temp = useRoots_C.front().points[0].Normalized();
			lightPos = temp * 10000.0f;
			lightPos.y = 40000.0f;
			lightDir = -temp;
			SetLightPosition(lightPos);
			SetLightDirection(-lightPos.Normalized());
		}

		backAlpha -= Time::DeltaTime * 3.0f;

		if (time + 0.1f <= useRoots_C.front().moveTime)
		{
			prePos = cameraPos;

			float nowTime = time / useRoots_C.front().moveTime;
			float targetTime = nowTime + 0.05f;

			switch (useRoots_C.front().moveNum)
			{
			case 2:
				cameraPos = Lerp(nowTime, useRoots_C.front().points);
				targetPos = Lerp(targetTime, useRoots_C.front().points);
				break;
			case 3:
				cameraPos = BeziersCurve3(nowTime, useRoots_C.front().points);
				targetPos = BeziersCurve3(targetTime, useRoots_C.front().points);
				break;
			case 4:
				if (useRoots_C.size() == 1)
				{
					cameraPos = BeziersCurve4(bez.Get(CBezier::eNoAccel, CBezier::eNoAccel, nowTime), useRoots_C.front().points);
					targetPos = BeziersCurve4(bez.Get(CBezier::eNoAccel, CBezier::eNoAccel, targetTime), useRoots_C.front().points);
				}
				else
				{
					cameraPos = BeziersCurve4(nowTime, useRoots_C.front().points);
					targetPos = BeziersCurve4(targetTime, useRoots_C.front().points);
				}

				break;
			default:
				useRoots_C.clear();
				break;
			}
		}
		else
		{
			velocity = cameraPos - prePos;
			time = 0.0f;
			useRoots_C.pop_front();
			if (useRoots_C.size() == 0)
				fade = !fade;
		}

		time += Time::DeltaTime / 2.0f;
	}

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

// 線形補間
Vector3 TitleCameraActor::Lerp(float sec, Vector3 points[2])
{
	Vector3 result;
	result = Vector3::Lerp(points[0], points[1], sec);

	return result;
}

// ベジエ移動
Vector3 TitleCameraActor::BeziersCurve3(float sec, Vector3 points[3])
{
	float b = sec;
	float a = 1.0f - b;

	/* 位置算出 */
	Vector3 result;
	result.x = a*a*points[0].x + 2 * a*b*points[1].x + b*b*points[2].x;
	result.y = a*a*points[0].y + 2 * a*b*points[1].y + b*b*points[2].y;
	result.z = a*a*points[0].z + 2 * a*b*points[1].z + b*b*points[2].z;

	return result;
}

// ベジエ移動
Vector3 TitleCameraActor::BeziersCurve4(float sec, Vector3 points[4])
{
	float b = sec;
	float a = 1.0f - b;

	/* 位置算出 */
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
const int CSV_POSITOIN  = 1;
const int CSV_OFFSET	= 4;
const int CSV_MOVE_TIME = 7;
void TitleCameraActor::AddRootList()
{
	RootData root;
	// 頂点数取得
	root.pointNum = csv_.getf(currentRow_, CSV_POINT_NUM);
	// 時間取得
	root.moveTime = csv_.getf(currentRow_, CSV_MOVE_TIME);
	// オフセット取得
	const Vector3 offset(
		csv_.getf(currentRow_, CSV_OFFSET + 0),
		csv_.getf(currentRow_, CSV_OFFSET + 0),
		csv_.getf(currentRow_, CSV_OFFSET + 0));
	// 座標取得
	for (int i = 0; i < root.pointNum; i++)
	{
		const Vector3 position(
			csv_.getf(currentRow_, CSV_POSITOIN + 0),
			csv_.getf(currentRow_, CSV_POSITOIN + 1),
			csv_.getf(currentRow_, CSV_POSITOIN + 2));
		root.points[i] = position;// *Vector3(2.3f, 1.5f, 2.3f) + Vector3(0.0f, 250.0f, 0.0f);
		currentRow_++;
	}
	// 保存
	roots.push_back(root);
}

void TitleCameraActor::GetRoot(int num)
{
	useRoots_C.clear();

	Vector3 p1, p2, centerPos, vecA, vecB;
	float length = 0.0f, lenA = 0.0f, lenB = 0.0f;

	// 保存されたルートデータ
	RootData rootData = roots[num];
	// これから使うルートデータ
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
		// 保存
		useRoots_C.push_back(root);
		break;
	case 3:
		for (int i = 0; i < 3; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.moveNum  = rootData.pointNum;
		root.moveTime = rootData.moveTime;
		// 保存
		useRoots_C.push_back(root);
		break;
	case 4:
		for (int i = 0; i < 4; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.moveNum  = rootData.pointNum;
		root.moveTime = rootData.moveTime;
		// 保存
		useRoots_C.push_back(root);
		break;
	case 6:
		// 頂点数
		root.moveNum = 4;

		// 中間点
		p1 = rootData.points[2];
		p2 = rootData.points[3];
		centerPos = p1 + (p2 - p1) / 2.0f;

		// 距離を算出
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

		/* ルートA */
		// 座標の保存
		for (int i = 0; i < 3; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.points[3] = centerPos;
		// 時間の算出
		for (int i = 1; i < 4; i++)
		{
			lenA += (root.points[i] - root.points[i - 1]).Length();
		}
		root.moveTime = rootData.moveTime * (lenA / length);

		// ルートA保存
		useRoots_C.push_back(root);

		/* ルートB */
		// 座標の保存
		root.points[0] = centerPos;
		for (int i = 1; i < 4; i++)
		{
			root.points[i] = rootData.points[i + 2];
		}
		// 時間の算出
		for (int i = 1; i < 4; i++)
		{
			lenB += (root.points[i] - root.points[i - 1]).Length();
		}
		root.moveTime = rootData.moveTime * (lenB / length);

		// ルートB保存
		useRoots_C.push_back(root);
		break;
	default:
		useRoots_C.clear();
		break;
	}

}

void TitleCameraActor::RootUpdate(std::list<SetRoot> root_)
{
	// ルートを取得
	if (root_.size() == 0)
	{
		rootCount %= maxRootCount;
		GetRoot(rootCount);
		rootCount++;
	}

	backAlpha -= Time::DeltaTime * 5.0f;

	if (time + 0.1f <= root_.front().moveTime)
	{
		float nowTime = time / root_.front().moveTime;
		float targetTime = nowTime + 0.1f;

		switch (root_.front().moveNum)
		{
		case 2:
			cameraPos = Lerp(nowTime, root_.front().points);
			targetPos = Lerp(targetTime, root_.front().points);
			break;
		case 3:
			cameraPos = BeziersCurve3(nowTime, root_.front().points);
			targetPos = BeziersCurve3(targetTime, root_.front().points);
			break;
		case 4:
			if (root_.size() == 1)
			{
				cameraPos = BeziersCurve4(bez.Get(CBezier::eNoAccel, CBezier::eNoAccel, nowTime), root_.front().points);
				targetPos = BeziersCurve4(bez.Get(CBezier::eNoAccel, CBezier::eNoAccel, targetTime), root_.front().points);
			}
			else
			{
				cameraPos = BeziersCurve4(nowTime, root_.front().points);
				targetPos = BeziersCurve4(targetTime, root_.front().points);
			}

			break;
		default:
			root_.clear();
			break;
		}
	}
	else
	{
		velocity = cameraPos - prePos;
		time = 0.0f;
		root_.pop_front();
		if (root_.size() == 0)
			fade = !fade;
	}

	time += Time::DeltaTime;
}

void TitleCameraActor::GetRoot(std::list<SetRoot> root_, int num)
{
	root_.clear();

	Vector3 p1, p2, centerPos, vecA, vecB;
	float length = 0.0f, lenA = 0.0f, lenB = 0.0f;

	// 保存されたルートデータ
	RootData rootData = roots[num];
	// これから使うルートデータ
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
		// 保存
		root_.push_back(root);
		break;
	case 3:
		for (int i = 0; i < 3; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.moveNum = rootData.pointNum;
		root.moveTime = rootData.moveTime;
		// 保存
		root_.push_back(root);
		break;
	case 4:
		for (int i = 0; i < 4; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.moveNum = rootData.pointNum;
		root.moveTime = rootData.moveTime;
		// 保存
		root_.push_back(root);
		break;
	case 6:
		// 頂点数
		root.moveNum = 4;

		// 中間点
		p1 = rootData.points[2];
		p2 = rootData.points[3];
		centerPos = p1 + (p2 - p1) / 2.0f;

		// 距離を算出
		for (int i = 1; i < 6; i++)
		{
			Vector3 v = rootData.points[i] - rootData.points[i - 1];
			length += v.Length();
		}

		/* ルートA */
		// 座標の保存
		for (int i = 0; i < 3; i++)
		{
			root.points[i] = rootData.points[i];
		}
		root.points[3] = centerPos;
		// 時間の算出
		for (int i = 1; i < 4; i++)
		{
			lenA += (root.points[i] - root.points[i - 1]).Length();
		}
		root.moveTime = rootData.moveTime * (lenA / length);

		// ルートA保存
		useRoots_C.push_back(root);

		/* ルートB */
		// 座標の保存
		root.points[0] = centerPos;
		for (int i = 1; i < 4; i++)
		{
			root.points[i] = rootData.points[i + 2];
		}
		// 時間の算出
		for (int i = 1; i < 4; i++)
		{
			lenB += (root.points[i] - root.points[i - 1]).Length();
		}
		root.moveTime = rootData.moveTime * (lenB / length);

		// ルートB保存
		root_.push_back(root);
		break;
	default:
		root_.clear();
		break;
	}
}
