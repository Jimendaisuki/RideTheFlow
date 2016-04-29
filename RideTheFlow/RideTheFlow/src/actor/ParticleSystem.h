#pragma once
#include "Actor.h"
#include <vector>

enum PARTICLE_SHAPE
{
	BEGIN,
	SPHERE,
	HALF_SPHERE,
	BOX,
	CORN,
	END
};

class ParticleSystem :public Actor
{
public:
	class Particle
	{
	public:
		Particle();
		void Initialize(
			const Vector3& pos_ , 
			const Vector3& vec_ = Vector3::One,
			float speed_ = 1.0f,
			float size_ = 1.0f,
			float alpha_ = 255.0f,
			float addSpeed_ = 0.0f,
			float addSize_ = 0.0f,
			float addAlpha_ = 0.0f);
		void Update();
		void Draw(const MODEL_ID& drawID, Vector2 origin = Vector2::Zero, const int& blend_mode = BLEND_MODE::NoBlend) const;
	private:
		//座標
		Vector3 pos;
		//移動方向
		Vector3 vec;
		//弾速
		float speed;
		//弾速度変化量
		float addSpeed;
		//画像拡大率
		float size;
		//画像拡大率変化量
		float addSize;
		//アルファ値
		float alpha;
		//アルファ値変化量
		float addAlpha;
	};

public:
	///<summary>球状、もしくは半球状に放出するパーティクルを生成します。</summary>
	///<param name = "world">ワールド</param>
	ParticleSystem(
		//ワールド
		IWorld& world,
		//描画する2D画像のID
		const MODEL_ID& drawID_,
		//放出間隔（秒）
		float intervalSec_,
		int sameEmissiveNum_,
		float lifeTime_,
		float lifeTimeLimit_,
		const Vector3& basePos_,
		float initSpeed_ = 1.0f,
		float initSize_ = 1.0f,
		float initAlpha_ = 255.0f,
		const Vector2& billboardOrigin_ = Vector2::Zero,
		float addSpeed_ = 0.0f,
		float addSize_ = 0.0f,
		float addAlpha_ = 0.0f,
		int blendMode_ = BLEND_MODE::NoBlend
		);
	~ParticleSystem();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//==============共通===============//
	//パーティクルを保管
	std::vector<Particle> particles;
	//描画する画像
	MODEL_ID drawID;
	//放出間隔(秒)
	float intervalSec;	
	//一度に放出する数
	int sameEmissiveNum;

	//持続時間計測用
	float lifeTime;
	//持続最高時間
	float lifeTimeLimit;

	//画像中心位置
	Vector2 billboardOrigin;
	//放出の中心、基準となる位置
	Vector3 basePos;

	//弾初速
	float initSpeed;
	//画像拡大率
	float initSize;
	//アルファ値
	float initAlpha;

	//弾速度変化量
	float addSpeed;
	//画像拡大率変化量
	float addSize;
	//アルファ値変化量
	float addAlpha;

	//ブレンドモード
	int blendMode;
	
	//タイマー
	float emissiveTimer;

	//==============BOX、CORN共通===============//
	//放出する方向の基準
	Vector3 vec;

	//==============BOX===============//
	//放出する箱の大きさ
	Vector3 boxSize;

};