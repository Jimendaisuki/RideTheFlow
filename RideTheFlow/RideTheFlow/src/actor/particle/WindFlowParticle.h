#pragma once

#include "Particle.h"
#include <vector>
#include "WindFlow.h"

class WindFlowParticle:public Particle
{
public:
	//(システム本体,ダッシュ時の軌跡,生成する高さ)
	WindFlowParticle(WindFlow& windflow_,const std::vector<Vector3>& dashPositions_, float positionHeight_);

	void OnUpdate() override;
	void Draw() const override;

private:
	WindFlow& windFlow;
	//プレイヤーのダッシュの軌跡
	std::vector<Vector3> dashPositions;
	//位置をずらして幅をもたせる
	Vector3 randomPosition;

	//パーティクルが動くワールド上のY値
	float positionHeight;

	//回転
	Vector3 rotate;
};