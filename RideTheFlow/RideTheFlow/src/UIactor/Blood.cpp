#include "Blood.h"
#include "../game/Random.h"
#include "../math/Math.h"
#include "../time/Time.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"

const float deadTime = 2.0f;
const float offset = 20.0f;

// 中心座標
const Vector2 Center = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
// 楕円半径
const Vector2 Radius = Vector2(WINDOW_WIDTH / 2 + offset, WINDOW_HEIGHT / 2 + offset * 2);

Blood::Blood(IWorld& world_, const Vector3 position_) :
UIActor(world_)
{
	parameter.isDead = false;
	parameter.id	 = UI_ID::BLOOD_UI;

	/* 初期設定 */
	alpha     = 1.0f;
	alphaTime = deadTime;
	scale  = Vector2(0.5f) * Random::GetInstance().Range(0.5f, 1.5f);
	rotate = Random::GetInstance().Range(0.0f, 359.0f);

	/* カメラ位置取得 */
	//Vector3 cameraPos = world_.GetCamera()->GetParameter().mat.GetPosition();
	Vector3 cameraPos = Camera::GetInstance().Position.Get();

	/* カメラからの各種ベクトル */
	// カメラ→プレイヤー
	Vector3 C_to_Pvec = world_.GetPlayer()->GetParameter().mat.GetPosition() - cameraPos;
	// カメラ→エネミー
	Vector3 C_to_Evec = position_ - cameraPos;
	/* なす角 */
	float angle = Math::Degree(Vector2::Inner(Vector2(C_to_Pvec.x, C_to_Pvec.z).Normalized(), Vector2(C_to_Evec.x, C_to_Evec.z).Normalized()));
	//float angle = Vector2::Inner(Vector2(C_to_Pvec.x, C_to_Pvec.z), Vector2(C_to_Evec.x, C_to_Evec.z));

	/* 右か左か */
	Vector2 Normal = Vector2(-C_to_Pvec.z, C_to_Pvec.x).Normalized();
	float dot = Vector2::Dot(Normal, Vector2(C_to_Evec.x, C_to_Evec.z));
	if (dot <= 0) position = Center + Vector2(Radius.x * Math::Sin(angle), Radius.y * Math::Cos(180.0f - angle));
	else position = Center + Vector2(-Radius.x * Math::Sin(angle), Radius.y * Math::Cos(180.0f - angle));

	/* 最後に各個ずらす */
	position += Vector2(Random::GetInstance().Range(-100, 100), Random::GetInstance().Range(-30, 30));
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