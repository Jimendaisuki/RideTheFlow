#include "Camera.h"
#include <Dxlib.h>
#include "../math/Math.h"

// カメラの更新処理
void Camera::Update()
{
	SetCameraPositionAndTargetAndUpVec(VGet(Position.Get().x, Position.Get().y, Position.Get().z),
		VGet(Target.Get().x, Target.Get().y, Target.Get().z),
		VGet(Up.Get().x, Up.Get().y, Up.Get().z));
}

// カメラの描画距離を設定する（手前距離、奥距離）
void Camera::SetRange(float Near, float Far)
{
	SetCameraNearFar(Near, Far);
}

// カメラの回転角度を設定する（座標、垂直回転角度・水平回転角度・捻り回転角度）
void Camera::SetRotation(Vector3 rotate)
{
	SetCameraPositionAndAngle(VGet(Position.Get().x, Position.Get().y, Position.Get().z), rotate.x, rotate.y, rotate.z);
}

// 指定した座標がカメラの視界に入っているか否か
int Camera::IsCheckView(Vector3 position)
{
	return CheckCameraViewClip(VGet(position.x, position.y, position.z));
}

void Camera::SetViewAngle(float degree)
{
	SetupCamera_Perspective(Math::Radian(degree));
}