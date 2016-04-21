#ifndef SPRING_CAMERA_ACTOR_H_
#define SPRING_CAMERA_ACTOR_H_
#include "Actor.h"

class SpringCameraActor :public Actor
{
public:
	SpringCameraActor(IWorld& world);
	~SpringCameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Matrix4 playerMat;
	Vector3 position;
	Vector3 point;
	Vector3 velocity;
	Vector3 restPosition;
	float stiffness;
	float friction;
	float mass;
};

#endif