#pragma once
#include "../Actor.h"
#include <vector>
#include <memory>
#include "ParticleSystem.h"
#include "../tornado/Tornado.h"

//壊れる城を選択
enum CASTLE_SELECT
{
	MASTER_CASTLE,
	CHILD_CASTLE,
};

//壊れ方を選択
enum BREAK_SELECT
{
	//竜巻
	TORNADO,
	//流れ
	WIND_FLOW,
	//空気砲
	WIND_BALL,
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

	void CastleEmissive(const Vector3& vec_);
	Vector3 RandomVelocity();

private:
	Vector3 velocity;
	//城と壊れ方をコンストラクタで選択
	CASTLE_SELECT castleSelect;
	BREAK_SELECT breakSelect;
};