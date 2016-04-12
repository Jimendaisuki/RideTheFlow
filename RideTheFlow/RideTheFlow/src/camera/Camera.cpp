#include "Camera.h"
#include <Dxlib.h>

Camera::Camera()
{
	
}

// カメラの描画距離を設定する（手前距離、奥距離）
void Camera::SetRange(float Near, float Far)
{
	SetCameraNearFar(Near, Far);
}

// カメラの更新処理
void Camera::Update()
{
	SetCameraPositionAndTargetAndUpVec(	VGet(Position.get().x, Position.get().y, Position.get().z),
										VGet(Target.get().x, Target.get().y, Target.get().z),
										VGet(Up.get().x, Up.get().y, Up.get().z));
}

// カメラの回転角度を設定する（座標、垂直回転角度・水平回転角度・捻り回転角度）
void Camera::SetRotation(Vector3 rotate)
{
	SetCameraPositionAndAngle(VGet(Position.get().x, Position.get().y, Position.get().z), rotate.x, rotate.y, rotate.z);
}

// 指定した座標がカメラの視界に入っているか否か
int Camera::IsCheckView(Vector3 position)
{
	return CheckCameraViewClip(VGet(position.x, position.y, position.z));
}