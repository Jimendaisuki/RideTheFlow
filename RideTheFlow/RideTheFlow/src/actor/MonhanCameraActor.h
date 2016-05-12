#ifndef MONHAN_CAMERA_ACTOR_H_
#define MONHAN_CAMERA_ACTOR_H_
#include "Actor.h"

struct SpringParameter{
	//ÉoÉlÇÃã≠Ç≥
	float stiffness;
	//ñÄéC
	float friction;
	//èdÇ≥
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
	Matrix4 playerMat;
	Vector3 position;
	Vector3 restPosition;
	Vector3 velocity;
	Vector3 targetPos;
	Vector3 posSeveStart;
	Vector3 posSeveEnd;
	SpringParameter springParameter;
	float fov;
	float rotateLeft;
	float rotateUp;
	float leapTimer;
	bool posSeve;
};

#endif