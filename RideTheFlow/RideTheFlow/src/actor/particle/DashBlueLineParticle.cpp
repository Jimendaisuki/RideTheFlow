#include "DashBlueLineParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"

DashBlueLineParticle::DashBlueLineParticle( const std::vector<Vector3>& dashPositions_, float positionHeight_)
:
dashPositions(dashPositions_),
randomPosition(Random::GetInstance().Range(-10.0f, 10.0f), 0.0f, Random::GetInstance().Range(-10.0f, 10.0f)),
positionHeight(positionHeight_),
rotate(Vector3::Zero)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 0.03f * dashPositions.size();
	lifeParam.isDead = false;

	moveParam.pos = dashPositions.at(0);

	drawParam.drawID = MODEL_ID::WIND_BLUE_MODEL;
	drawParam.size = 15.0f;
	drawParam.alpha = 1.0f;
	drawParam.blendMode = BLEND_MODE::Alpha;
	drawParam.billboardOrigin = Vector2(0, 0);
}

void DashBlueLineParticle::OnUpdate()
{
	int size = dashPositions.size();

	//要素数が足りない場合ははじく
	if (size < 3)
		return;

	//ダッシュの軌跡をなぞる
	int num = size - (size * (lifeParam.lifeTime / lifeParam.lifeTimeLimit));
	//範囲外へ行かないように止める
	if (num > size - 1 || num < 0)
		return;

	//表示する座標を計算　ダッシュの軌跡からランダムな値分ずらす
	moveParam.pos = dashPositions.at(num) + randomPosition;
	//Yの値は渡されてきたもので固定
	moveParam.pos.y = positionHeight;

	//アルファ値計算
	drawParam.alpha = 1.0f * Math::Cos((lifeParam.lifeTime / lifeParam.lifeTimeLimit) * 90.0f);

	//最初のうちは向きの計算をしない
	if (num < 1)
		return;
	//進行方向
	Vector3 v = Vector3::Normalize(dashPositions.at(num) - dashPositions.at(num - 1));
	//回転計算
	rotate.y = Math::Degree(Math::Atan2(v.x, v.z));

}

void DashBlueLineParticle::Draw() const
{
	Model::GetInstance().Draw(drawParam.drawID, moveParam.pos, drawParam.alpha, rotate, drawParam.size, true);
}
