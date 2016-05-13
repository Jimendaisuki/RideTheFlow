#pragma once
#include "Actor.h"
#include <vector>

//ダッシュ時に生成する流れ
class WindFlow :public Actor
{
public:
	WindFlow(IWorld& world, std::vector<Vector3>& positions_);
	~WindFlow();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	std::vector<Vector3> positions;

private:
	//座標分割数
	static const int SplitNum;
	//流れの高さ最低値　流れの高さ～最低値までが縦の長さ
	static const float HeightMin;
};