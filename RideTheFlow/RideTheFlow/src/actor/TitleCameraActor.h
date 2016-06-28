#pragma once
#include "Actor.h"
#include "../UIactor/Beziers.h"
#include "../UIactor/CsvReader.h"

class TitleCameraActor : public Actor
{
struct RootData
{
	int		pointNum = 0;
	float	moveTime = 0;
	Vector3 points[6];
};

struct SetRoot
{
	int		moveNum;
	float	moveTime;
	Vector3 points[4];
};

public:
	TitleCameraActor(IWorld& world);
	~TitleCameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 Lerp(float sec, Vector3[]);
	Vector3 BeziersCurve3(float sec, Vector3 points[]);
	Vector3 BeziersCurve4(float sec, Vector3 points[]);
	void RootLoad();
	void AddRootList();
	void GetRoot(int num);

	void RootUpdate(std::list<SetRoot> root);
	void GetRoot(std::list<SetRoot> root, int num);


private:
	Vector3 cameraPos;
	Vector3 targetPos;
	Vector3 prePos;
	Vector3 velocity;
	float	time;
	float	backAlpha;
	bool	fade;
	int		rootCount;
	int		maxRootCount;

	CBezier				  bez;
	CsvReader			  csv_;
	int					  currentRow_;
	std::vector<RootData> roots;
	std::list<SetRoot>	  useRoots_C;
	std::list<SetRoot>	  useRoots_T;

	Vector3 lightPos;
	Vector3 lightDir;
};