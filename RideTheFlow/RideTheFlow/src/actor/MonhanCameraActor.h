#ifndef MONHAN_CAMERA_ACTOR_H_
#define MONHAN_CAMERA_ACTOR_H_
#include "Actor.h"

struct SpringParameter{
	//�o�l�̋���
	float stiffness;
	//���C
	float friction;
	//�d��
	float mass;
};

class MonhanCameraActor :public Actor
{
public:
	MonhanCameraActor(IWorld& world);
	~MonhanCameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 DefaultCamera();
	Vector3 DashCmaera();
	float SpringFov(float rest, float pos);
	Vector3 SpringTarget();


private:
	Matrix4 playerMat;
	Vector3 position;

	//�o�l�J�����֌W
	Vector3 restPosition;
	Vector3 velocity;
	Vector3 cameraTarget;
	Vector3 restCameraTarget;
	SpringParameter springParameter;
	SpringParameter springTargetParameter;
	float fov;
	float rotateLeft;
	float rotateUp;

	//�^�b�N���֌W
	Vector3 posSeveStart;
	Vector3 posSeveEnd;
	Vector3 playerPosSeve;
	Vector3 targetVelo;
	float targetY;
	float leapTimer;
	float restLeapTimer;
	float tackleLeapTimer;
	bool posMove1;
	bool posMove2;
	bool posEnd;

	//�_�b�V��
	bool cameraFovFlag;
	bool cameraFovEndFlag;
	float restRotate;
	float rotateVelo;
	float fovVelo;
};

#endif