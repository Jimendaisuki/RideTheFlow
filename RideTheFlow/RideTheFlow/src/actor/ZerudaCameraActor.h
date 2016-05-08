#ifndef ZERUDA_CAMERA_ACTOR_H_
#define ZERUDA_CAMERA_ACTOR_H_
#include "Actor.h"

class ZerudaCameraActor :public Actor
{
public:
	ZerudaCameraActor(IWorld& world);
	~ZerudaCameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Matrix4 playerMat;
	Vector3 position;
	Vector3 restPosition;
	Vector3 velocity;
	float stiffness;
	float friction;
	float mass;
	float rotateLeft;
	float rotateUp;
};

#endif