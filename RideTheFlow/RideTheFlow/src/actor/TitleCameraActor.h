#pragma once
#include "Actor.h"

class TitleCameraActor : public Actor
{
public:
	TitleCameraActor(IWorld& world);
	~TitleCameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	void SetFrame(int num);
	void Liner(float sec);
	//void Liner();
	void BeziersCurve(float sec);
	//void BeziersCurve();

private:
	Vector3 cameraPos;
	Vector3 targetPos;
	Vector3 startPos;
	Vector3 endPos;
	Vector3 p;
	Vector3 prePos;
	float	time;
	int stageModelHandle;

	std::vector<Vector3> frames;
	std::vector<float> parentFrames;
};