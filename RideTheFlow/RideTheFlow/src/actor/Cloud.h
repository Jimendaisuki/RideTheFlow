#pragma once
#include "Actor.h"
#include <vector>
#include <memory>

//雲
class Cloud :public Actor, public std::enable_shared_from_this<Cloud>
{
public:
	Cloud(IWorld& world, const Vector3& position_);
	~Cloud();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

	//数値リセット
	void Reset();
	//ステージの外に出ているか？
	bool IsStageOut();

private:
	//雲の位置をばらつかせるための配列
	std::vector<Vector3> cloudPositions;
	//サイズ
	std::vector<float> cloudsizes;

	//現在の座標
	Vector3 position;
	//移動方向
	Vector3 moveVec;
	//移動速度
	float moveSpeed;
	//移動方向切り替え用タイマー
	float moveChangeTimer;
	float moveChangeTime;
	//流れから離れた時間タイマー
	float windOutTimer;

	//セルフビルボード計算用、カメラから計算
	Vector3 up;
	Vector3 front;
	Vector3 left;
};