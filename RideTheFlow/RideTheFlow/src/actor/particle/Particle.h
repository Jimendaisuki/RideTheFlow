#pragma once

#include "../../math/Vector2.h"
#include "../../math/Vector3.h"
#include "../../graphic/Model.h"

struct ParticleLifeParameter
{
	//生存時間
	float lifeTime;
	//パーティクル寿命
	float lifeTimeLimit;
	//寿命を迎えたか？
	bool isDead;
};

struct ParticleMoveParameter
{
	//座標
	Vector3 pos;
	//移動方向
	Vector3 vec;
	//弾速
	float speed;
	//弾速度変化量
	float addSpeed;
};

struct ParticleDrawParameter
{
	//描画するモデルID
	MODEL_ID drawID;
	//拡大率
	float size;
	//拡大率変化量
	float addSize;
	//アルファ値
	float alpha;
	//アルファ値変化量
	float addAlpha;
	//ブレンドモード
	int blendMode;
	//画像中心位置
	Vector2 billboardOrigin;
};

class Particle
{
public:
	Particle(
		const MODEL_ID& id_,
		float lifeLimit_,
		const Vector3& pos_,
		const Vector3& vec_ = Vector3::Zero,
		float speed_ = 1.0f,
		float addSpeed_ = 0.0f,
		float size_ = 1.0f,
		float addSize_ = 0.0f,
		float alpha_ = 255.0f,
		float addAlpha_ = 0.0f,
		int blendMode_ = BLEND_MODE::NoBlend,
		const Vector2& origin_ = Vector2::Zero);

	void Update();
	void Draw() const;
	bool GetIsDead();

private:
	ParticleLifeParameter lifeParam;
	ParticleMoveParameter moveParam;
	ParticleDrawParameter drawParam;
};