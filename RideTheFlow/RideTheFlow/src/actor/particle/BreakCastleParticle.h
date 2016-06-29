#pragma once

#include "Particle.h"
#include "BreakCastle.h"
#include <vector>

class BreakCastleParticle :public Particle
{
public:
	//モデルID、壊れ方、システムの座標、座標、移動方向*移動量、初期回転X、初期回転Y
	BreakCastleParticle(const MODEL_ID& id_, const BREAK_SELECT& break_, Vector3* parentPosition_,const Vector3& position_, const Vector3& vec_, float rotX_, float rotY_ , float scale_);

	void OnUpdate() override;
	void Draw() const override;

private:
	//竜巻による壊れ方
	void TornadoBreak();
	//流れによる壊れ方
	void WindFlowBreak();
	//空気砲による壊れ方
	void WindBallBreak();
	//ダメージ
	void DamageBreak();

private:
	//壊れ方
	BREAK_SELECT breakSelect;
	//管理者であるBreakCastleの座標
	Vector3* pParentPosition;
	//軸周りの回転量
	float rotX, rotY;
	//回転
	Matrix4 rotmat;
	//最終的なマトリックス
	Matrix4 mat;

	//竜巻
	float rotXSpeed,rotYSpeed;
	float rotXAdd, rotYAdd;
	float risingSpeed;
	float tornadeRadius;
	float tornadeDegree;
	float tornadeAddRadius;
	float tornadeSpeed;
	Vector3 tornadeAddPosition;

	//流れ
	float flowRisingSpeed;
	float flowRotXSpeed, flowRotYSpeed;
	float flowRotXAdd, flowRotYAdd;
	Vector3 flowAddPosition;

	//空気砲
	float ballRotXSpeed, ballRotYSpeed;
};