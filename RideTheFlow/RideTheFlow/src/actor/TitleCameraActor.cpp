#include "TitleCameraActor.h"
#include "Collision.h"
#include "../camera/Camera.h"
#include "../graphic/Model.h"
#include "../time/Time.h"
#include "../world/IWorld.h"

/* メモ 
Draw部分でｙ軸が-100されているため、
2回目以降のboneの位置が-100されている模様
どこかでリセット
*/

TitleCameraActor::TitleCameraActor(IWorld& world) :
Actor(world),
time(0.0f)
{
	parameter.id = ACTOR_ID::CAMERA_ACTOR;
	parameter.isDead = false;

	stageModelHandle = Model::GetInstance().GetHandle(MODEL_ID::STAGE_MODEL);

	MV1ResetFrameUserLocalMatrix(stageModelHandle, 2);
	MV1ResetFrameUserLocalMatrix(stageModelHandle, 3);

	/* ステージ内のフレームを保存 */
	// テスト用でメッシュ含むので初期０
	frames.clear();
	for (int i = 0; i < MV1GetFrameNum(stageModelHandle); i++)
		frames.push_back(Vector3::ToVECTOR(MV1GetFramePosition(stageModelHandle, i)));
	
	frameIndex = 0;

	SetFrame(frameIndex);
	targetPos = startPos;
	cameraPos = targetPos - (Vector3::Normalize(endPos - startPos) * 5.0f) * Vector3(1.0f, 0.0f, 1.0f);

	MV1ResetFrameUserLocalMatrix(stageModelHandle, 3);
	MV1ResetFrameUserLocalMatrix(stageModelHandle, 2);
	MV1ResetFrameTextureAddressTransform(stageModelHandle, 2);
	MV1ResetFrameTextureAddressTransform(stageModelHandle, 3);

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
}

TitleCameraActor::~TitleCameraActor()
{
	MV1ResetFrameUserLocalMatrix(stageModelHandle, 3);
	MV1ResetFrameUserLocalMatrix(stageModelHandle, 2);
	MV1ResetFrameTextureAddressTransform(stageModelHandle, 2);
	MV1ResetFrameTextureAddressTransform(stageModelHandle, 3);

	frames.clear();
}
void TitleCameraActor::Update()
{
	time += Time::DeltaTime;
	if (time > 2)
	{
		//time = 0;
		frameIndex += 2;
		if (frameIndex >= frames.size() - 1) frameIndex = 0;
		SetFrame(frameIndex);
	}

	//Liner(2.0f);
	BeziersCurve(2.0f);

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

// カメラフレームセット
void TitleCameraActor::SetFrame(int num)
{
	startPos = frames[num];
	endPos	 = frames[num + 1];
}

// 直線移動
void TitleCameraActor::Liner(float sec)
{
	targetPos = Vector3::Lerp(startPos, endPos, time / sec);
	cameraPos = targetPos - ((endPos - startPos) * Vector3(1.0f, 0.0f, 1.0f)).Normalized() * 10.0f;

	if (time >= sec) time = 0;
}

// ベジエ移動
float px, py, pz, pre_x = 0, pre_y = 0, pre_z = 0;
void TitleCameraActor::BeziersCurve(float sec)
{
	float b = time / sec;
	float a = 1 - b;

	/* 現状仮の値を代入 */
	px = a * a * a * frames[1].x + 3 * a*a*b*frames[3].x + 3 * a*b*b*frames[5].x + b*b*b*frames[7].x;
	py = a * a * a * frames[1].y + 3 * a*a*b*frames[3].y + 3 * a*b*b*frames[5].y + b*b*b*frames[7].y;
	pz = a * a * a * frames[1].z + 3 * a*a*b*frames[3].z + 3 * a*b*b*frames[5].z + b*b*b*frames[7].z;

	targetPos = Vector3(px, py, pz);
	cameraPos = targetPos - (targetPos - Vector3(pre_x, pre_y, pre_z)).Normalized() * 50.0f;

	pre_x = px;
	pre_y = py;
	pre_z = pz;

	if (time >= sec) time = 0;
}