#include "Camera.h"
#include <Dxlib.h>
#include "../math/Math.h"
#include "../math/Matrix4.h"
#include "../input/Keyboard.h"

// カメラの更新処理
void Camera::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::F)){
		freeCamera = !freeCamera;
		free_Position = Position;
		free_Target.Set(free_Position.Get() + Vector3(0, 0, 1));
		startTarget = free_Target.Get();
		free_Up = Up;
		rotateUp = 0;
	}
	if (!freeCamera){
		SetCameraPositionAndTargetAndUpVec(VGet(Position.Get().x, Position.Get().y, Position.Get().z),
			VGet(Target.Get().x, Target.Get().y, Target.Get().z),
			VGet(Up.Get().x, Up.Get().y, Up.Get().z));
	}
	else{
		Vector3 vec = (free_Position.Get() - free_Target.Get()).Normalized();
		if (!Keyboard::GetInstance().KeyStateDown(KEYCODE::RSHIFT))
		beforeVec = vec;
		Vector3 left = Vector3::Cross(beforeVec, Vector3(0, 1, 0));
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::N)){
			speed -= 0.5f;
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::M)){
			speed += 0.5f;
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::V)){
			rotateSpeed -= 0.5f;
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::B)){
			rotateSpeed += 0.5f;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::U)){
			free_Position.Set(free_Position.Get() - beforeVec * speed);
			free_Target.Set(free_Target.Get() - beforeVec * speed);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::J)){
			free_Position.Set(free_Position.Get() + beforeVec * speed);
			free_Target.Set(free_Target.Get() + beforeVec * speed);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::K)){
			free_Position.Set(free_Position.Get() + left * speed);
			free_Target.Set(free_Target.Get() + left * speed);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::H)){
			free_Position.Set(free_Position.Get() - left * speed);
			free_Target.Set(free_Target.Get() - left * speed);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Y)){
			free_Position.Set(free_Position.Get() + Vector3(0,1,0) * speed);
			free_Target.Set(free_Target.Get() + Vector3(0, 1, 0) * speed);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::I)){
			free_Position.Set(free_Position.Get() - Vector3(0, 1, 0) * speed);
			free_Target.Set(free_Target.Get() - Vector3(0, 1, 0) * speed);
		}

		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
			rotateUp += rotateSpeed;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
			rotateUp -= rotateSpeed;

		free_Target.Set(startTarget * Matrix4::RotateY(rotateUp) + free_Position.Get());

		SetCameraPositionAndTargetAndUpVec(VGet(free_Position.Get().x, free_Position.Get().y, free_Position.Get().z),
			VGet(free_Target.Get().x, free_Target.Get().y, free_Target.Get().z),
			VGet(free_Up.Get().x, free_Up.Get().y, free_Up.Get().z));
	}
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