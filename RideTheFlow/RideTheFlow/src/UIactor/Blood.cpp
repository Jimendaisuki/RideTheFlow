#include "Blood.h"
#include "../game/Random.h"
#include "../math/Math.h"
#include "../time/Time.h"
#include "../Def.h"

#include "../actor/Actor.h"
#include "../world/IWorld.h"

/*
追加方法メモ
EnemuBullet.h
EnemyBullet(IWorld& world, Vector3 position, Actor& parent_);
.cpp
EnemyBullet::EnemyBullet(IWorld& world, Vector3 position, Actor& parent_) : 
parent = &parent_;

バレット生成しているアクター
world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, *this));


OnCollisin内
プレイヤーの場合
Effect::GetInstance().DamegeEffect(world, other.parent->GetParameter().mat.GetPosition());
バレットの場合
Effect::GetInstance().DamegeEffect(world, parent->GetParameter().mat.GetPosition());
*/

const float deadTime = 2.0f;
const float offset = 20.0f;

// 中心座標
const Vector2 Center = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
// 楕円半径
const Vector2 Radius = Vector2(300.0f, 200.0f);
Blood::Blood(IWorld& world, const Vector3 position_, const Vector3 front_) :
UIActor(world)
{
	parameter.isDead = false;
	parameter.id	 = EFFECT_ID::BLOOD_EFFECT;

	/* 初期設定 */
	alpha     = 1.0f;
	alphaTime = deadTime;
	scale  = Vector2(0.5f) * Random::GetInstance().Range(0.5f, 1.5f);
	rotate = Random::GetInstance().Range(0.0f, 359.0f);

	///* 位置を算出 */
	//Vector3 temp = ConvWorldPosToScreenPos(position_.ToVECTOR());
	//position = Vector2(
	//	Math::Clamp(temp.x, offset, (float)WINDOW_WIDTH - offset) + Random::GetInstance().Range(-20.0f, 20.0f),
	//	Math::Clamp(temp.y, offset, (float)WINDOW_HEIGHT - offset) + Random::GetInstance().Range(-20.0f, 20.0f));
	//
	///* カメラの裏側にいた場合の補正 */
	//if (temp.z >= 1)
	//{
	//	position.x = (WINDOW_WIDTH - position.x) + Random::GetInstance().Range(-20.0f, 20.0f);
	//	position.y = WINDOW_HEIGHT + Random::GetInstance().Range(-20.0f, 20.0f);
	//}

	float r = Vector2::Dot(Vector2(position_.x, position_.z).Normalized(), Vector2(front_.x, front_.z).Normalized());
	auto temp = r;
}

Blood::Blood(IWorld& world, const Vector3 position_, const Actor& player_) :
UIActor(world)
{
	parameter.isDead = false;
	parameter.id = EFFECT_ID::BLOOD_EFFECT;

	/* 初期設定 */
	alpha = 1.0f;
	alphaTime = deadTime;
	scale = Vector2(0.5f) * Random::GetInstance().Range(0.5f, 1.5f);
	rotate = Random::GetInstance().Range(0.0f, 359.0f);

	Vector3 cameraPos;

	world.EachActor(ACTOR_ID::CAMERA_ACTOR, [&](const Actor& other){
		cameraPos = other.GetParameter().mat.GetPosition();
	});

	/* 敵とプレイヤーの位置関係の計算 */
	Vector3 playerPosTemp = player_.GetParameter().mat.GetPosition();
	Vector2 playerPos = Vector2(playerPosTemp.x, playerPosTemp.z);
	Vector2 enemyPos = Vector2(position_.x, position_.z);

	// プレイヤーから敵へのベクトル
	Vector2 PtoEvec = enemyPos - playerPos;
	PtoEvec = PtoEvec.Normalized();
	// カメラベクトル
	Vector2 cameraFront = playerPos - Vector2(cameraPos.x, cameraPos.z);
	cameraFront = cameraFront.Normalized();
	Vector2 cameraLeft = Vector2(-cameraFront.y, cameraFront.x);
	cameraLeft = cameraLeft.Normalized();

	float dot = Vector2::Dot(cameraLeft, cameraFront);
	// dot > 0 上画面
	// dot < 0 下画面

	auto frontRotate = Math::Degree(Vector2::Inner(cameraFront, PtoEvec));
	auto cos = Math::Cos(frontRotate);
	if (Vector2::Dot(cameraLeft, PtoEvec) <= 0)
	{
		position.x = Center.x + Radius.x * Math::Cos(frontRotate);
	}
	else
	{
		position.x = Center.x - Radius.x * Math::Cos(frontRotate);
	}
	if (Vector2::Dot(cameraFront, PtoEvec) <= 0)
	{
		position.y = Center.y + Radius.y * Math::Sin(frontRotate);
	}
	else
	{
		position.y = Center.y - Radius.y * Math::Sin(frontRotate);
	}


	position;
}

Blood::~Blood()
{

}

void Blood::Update()
{
	if (alphaTime > 0)	alphaTime -= Time::DeltaTime;
	else alpha -= Time::DeltaTime;

	if (alpha <= 0) parameter.isDead = true;
}

void Blood::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::BLOOD_SPRITE, position, Vector2(262, 256), alpha, scale, rotate, true, false);
}