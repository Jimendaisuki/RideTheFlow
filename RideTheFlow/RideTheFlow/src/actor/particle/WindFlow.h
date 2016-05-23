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
	
	//ダッシュ時の軌跡を取得
	std::vector<Vector3>& GetDashPositions();
	//タックルヒット後に移動した距離を取得
	Vector3& GetMoveVec();

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	Player& player;
	//プレイヤーとは別に座標配列を保持（ダッシュ終了まで毎フレーム取得）
	std::vector<Vector3> dashPositions;
	//ダッシュ座標配列の取得が完了したか？
	bool isSetting;
	//タックルされた後の移動方向
	Vector3 vec;
	//タックルされた後の移動速度
	float speed;
	//初期位置からの移動量
	Vector3 move;
};