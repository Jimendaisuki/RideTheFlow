#ifndef MONHAN_CAMERA_ACTOR_H_
#define MONHAN_CAMERA_ACTOR_H_
#include "Actor.h"

class MonhanCameraActor :public Actor
{
public:
	MonhanCameraActor(IWorld& world);
	~MonhanCameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Matrix4 playerMat;
	Vector3 position;
	Vector3 restPosition;
	Vector3 velocity;
	Vector3 targetPos;
	Vector3 posSeveStart;
	Vector3 posSeveEnd;
	float fov;
	float stiffness;
	float friction;
	float mass;
	float rotateLeft;
	float rotateUp;
	float leapTimer;
	bool posSeve;
};

#endif