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
		Particle(
			const Vector3& pos_,
			const Vector3& vec_ = Vector3::One,
			float life_ = 1.0f,
			float speed_ = 1.0f,
			float size_ = 1.0f,
			float alpha_ = 255.0f,
			float addSpeed_ = 0.0f,
			float addSize_ = 0.0f,
			float addAlpha_ = 0.0f);
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
		bool GetIsDead();
	private:
		//パーティクル寿命
		float lifeTime;
		float lifeTimeLimit;
		bool isDead;
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
	///<summary>
	///球状、もしくは半球状に放出するパーティクルを生成します。
	///</summary>
	ParticleSystem(
		//ワールド
		IWorld& world,
		//描画する2D画像のID
		const MODEL_ID& drawID_,
		//放出間隔（秒）
		float intervalSec_,
		//同時発射数
		int sameEmissiveNum_,
		//生存時間
		float lifeTimeLimit_,
		//放出地点
		const Vector3& basePos_,
		//true:球状、false:半球状
		bool isShpere,
		//初期速度
		float initSpeed_ = 1.0f,
		//初期サイズ
		float initSize_ = 1.0f,
		//初期アルファ値
		float initAlpha_ = 255.0f,
		//画像中心位置
		const Vector2& billboardOrigin_ = Vector2::Zero,
		//速度増加量
		float addSpeed_ = 0.0f,
		//サイズ増加量
		float addSize_ = 0.0f,
		//アルファ値増加量
		float addAlpha_ = 0.0f,
		//ブレンド
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
	//放出する形状
	PARTICLE_SHAPE shape;
	//描画する画像
	MODEL_ID drawID;
	//放出間隔(秒)
	float intervalSec;
	//一度に放出する数
	int sameEmissiveNum;

	//寿命計測用
	float lifeTime;
	//寿命時間
	float lifeTimeLimit;

	//パーティクルに与える寿命
	float particleLifeTimeLimit;

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