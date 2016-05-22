#pragma once

#include "Particle.h"
#include <vector>

class WindFlowParticle:public Particle
{
public:
	WindFlowParticle(const std::vector<Vector3>& dashPositions_, float positionHeight_);

	void OnUpdate() override;
	void Draw() const override;

private:
	//プレイヤーのダッシュの軌跡
	std::vector<Vector3> dashPositions;
	//位置をずらして幅をもたせる
	Vector3 randomPosition;

	//パーティクルが動くワールド上のY値
	float positionHeight;

	//回転
	Vector3 rotate;
};