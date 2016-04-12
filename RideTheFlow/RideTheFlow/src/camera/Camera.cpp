#include "Camera.h"
#include <Dxlib.h>

Camera::Camera()
{
	
}

// �J�����̕`�拗����ݒ肷��i��O�����A�������j
void Camera::SetRange(float Near, float Far)
{
	SetCameraNearFar(Near, Far);
}

// �J�����̍X�V����
void Camera::Update()
{
	SetCameraPositionAndTargetAndUpVec(	VGet(Position.get().x, Position.get().y, Position.get().z),
										VGet(Target.get().x, Target.get().y, Target.get().z),
										VGet(Up.get().x, Up.get().y, Up.get().z));
}

// �J�����̉�]�p�x��ݒ肷��i���W�A������]�p�x�E������]�p�x�E�P���]�p�x�j
void Camera::SetRotation(Vector3 rotate)
{
	SetCameraPositionAndAngle(VGet(Position.get().x, Position.get().y, Position.get().z), rotate.x, rotate.y, rotate.z);
}

// �w�肵�����W���J�����̎��E�ɓ����Ă��邩�ۂ�
int Camera::IsCheckView(Vector3 position)
{
	return CheckCameraViewClip(VGet(position.x, position.y, position.z));
}