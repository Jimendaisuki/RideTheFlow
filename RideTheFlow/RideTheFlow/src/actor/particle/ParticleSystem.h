#pragma once
#include "../Actor.h"
#include "ParticlePtr.h"
#include <list>

//パーティクルシステムの、設定すべき数値構造体
struct ParticleSystemParameter
{
	//放出の中心、基準となる位置
	Vector3 position;

	//放出間隔(秒)
	float intervalSec;
	//一度に同時放出する数
	int sameEmissiveNum;

	//寿命時間
	float lifeTimeLimit;
	//寿命かどうか
	bool isDead;
	//システム生成時に１度放出を行うか？
	bool trigger;
};

class ParticleSystem
{
public:
	///<summary>
	///パーティクルの生成、一斉更新・描画管理クラス
	///</summary>
	ParticleSystem();
	~ParticleSystem();

	//保管しているパーティクルを更新
	void UpdateParticles();
	//保管しているパーティクルを描画
	void DrawParticles() const;

	//パーティクルの生成方法を記述（同時放出は勝手に行われるため、１行でok）
	virtual void Emissive() = 0;

	//パーティクルを追加
	void AddParticle(ParticlePtr particle);

	//死んでいるパーティクルを削除
	void RemoveDeadParticle();

	//パーティクルシステムが終了しているか？
	bool IsDeadSystem();

	ParticleSystemParameter GetPSParemeter()
	{
		return ps_parameter;
	}

	//残りの生存時間を返す
	float GetLifeTimeSub()
	{
		return ps_parameter.lifeTimeLimit - lifeTime;
	}

protected:
	//パーティクルを保管
	std::list<ParticlePtr> particles;

	//寿命計測用
	float lifeTime;
	//放出計測用
	float emissiveTimer;
	//初期放出完了フラグ
	bool isTriggerEnd;

	ParticleSystemParameter ps_parameter;
};