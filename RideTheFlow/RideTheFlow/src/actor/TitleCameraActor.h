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
	void Liner();

private:
	Vector3 cameraPos;
	Vector3 targetPos;
	Vector3 startPos;
	Vector3 endPos;
	float	time;
	int stageModelHandle;
	int frameIndex;

	std::vector<Vector3> frames;
};