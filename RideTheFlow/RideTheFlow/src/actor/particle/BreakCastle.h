#pragma once
#include "../Actor.h"
#include <vector>
#include <memory>
#include "ParticleSystem.h"
#include "../tornado/Tornado.h"
#include <functional>

//壊れる城を選択
enum CASTLE_SELECT
{
	//城
	MASTER_CASTLE,
	CHILD_CASTLE,
	//飛行船
	SHIP,
	//浮島
	ISLE1,
	ISLE2,
	ISLE3,
	//軍隊
	ARMY_ENEMY,
	//家
	HOME,
};

//壊れ方を選択
enum BREAK_SELECT
{
	BREAK_BEGIN,
	//竜巻
	TORNADO,
	//流れ
	WIND_FLOW,
	//空気砲
	WIND_BALL,
	DAMAGE,
	BREAK_END,
};

class BreakCastle :public Actor, public ParticleSystem, public std::enable_shared_from_this<BreakCastle>
{
public:
	//=======Actor======//
	BreakCastle(IWorld& world, const Vector3& position_, const CASTLE_SELECT& castle_, const BREAK_SELECT& break_);
	~BreakCastle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	//竜巻による壊れ方
	void TornadoBreakUpdate();
	void TornadoBreakEmissive();
	//流れによる壊れ方
	void WindFlowBreakUpdate();
	void WindFlowBreakEmissive();
	//空気砲による壊れ方
	void WindBallBreakUpdate();
	void WindBallBreakEmissive();
	//ダメージによる壊れ方
	void DamageEmissive();

	void CastleWindFlowBreakEmissive( float scale_);
	void MasterCastleEmissive(const Vector3& vec_,float scale_);

	void ShipEmissive(std::function<Vector3()> vecFunc);
	void ArmyEnemyEmissive(std::function<Vector3()> vecFunc);

	void CastleDamageEmissive(std::function<Vector3()> vecFunc);
	void ShipDamageEmissive(std::function<Vector3()> vecFunc);

	void HomeEmissive();

	Vector3 RandomVelocity();

private:
	Vector3 velocity;
	//城と壊れ方をコンストラクタで選択
	CASTLE_SELECT castleSelect;
	BREAK_SELECT breakSelect;

	//竜巻の動きについていく
	Tornado* pTornado;
};