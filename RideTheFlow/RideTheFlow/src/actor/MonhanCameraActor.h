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


private:
	Matrix4 playerMat;
	Vector3 position;

	//�o�l�J�����֌W
	Vector3 restPosition;
	Vector3 velocity;
	SpringParameter springParameter;
	float fov;
	float rotateLeft;
	float rotateUp;
	//���W�ۑ�
	Vector3 posSeveStart;
	Vector3 posSeveEnd;
	Vector3 playerPosSeve;
	//�^�b�N��
	float leapTimer;
	bool posMove1;
	bool posMove2;

	Vector3 test;
};

#endif