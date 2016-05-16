#pragma once
#include "../Actor.h"
#include <vector>
#include "../Player.h"
#include "ParticleSystem.h"

//ダッシュ時に生成する流れ
class WindFlow :public Actor,public ParticleSystem
{
public:
	//=======Actor======//
	WindFlow(IWorld& world, Player& player_);
	~WindFlow();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
	
	std::vector<Vector3>& GetDashPositions();

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	Player& player;
	//プレイヤーとは別に座標配列を保持（ダッシュ終了まで毎フレーム取得）
	std::vector<Vector3> dashPositions;
	//ダッシュ座標配列の取得が完了したか？
	bool isSetting;
};