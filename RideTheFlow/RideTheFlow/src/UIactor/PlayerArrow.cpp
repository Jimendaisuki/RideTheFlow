#include "PlayerArrow.h"
#include "FlowRoot.h"
#include "../world/IWorld.h"

const float Scale = 0.6f;
const Vector2 MAP_POSITION = Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) - Vector2(256) * Scale;
const Vector2 StageSize = Vector2(3000, 3000);
const float ReSIZE = 256.0f / StageSize.x * Scale;

PlayerArrow::PlayerArrow(IWorld& world, Player* player_) :
UIActor(world),
player(player_),
angle_(0),
isDash(false),
prevDash(false)
{
	parameter.isDead = false;
	parameter.id	 = UI_ID::PLAYER_ARROW_UI;

	int res = LoadGraph("res/Sprite/root.png");
	for (int i = 0; i < 10; i++)
		resPiece[i] = DerivationGraph(0, i * 10, 40, 20, res);
}

PlayerArrow::~PlayerArrow()
{

}

void PlayerArrow::Update()
{
	// アングル
	Vector3 playerFront = Vector3(player->GetParameter().mat.GetFront() * Vector3(1, 0, 1)).Normalized();
	if (playerFront.Length() != 0)
	{
		angle_ = Vector3::Inner(playerFront, -Vector3::Forward);
		if (Vector3::Dot(playerFront, Vector3::Left) > 0.0f)
			angle_ *= -1;
	}

	/* プレイヤーデータ */
	// ポジション
	Vector3 playerPos = player->GetParameter().mat.GetPosition();
	Vector2 pos = Vector2(playerPos.x, -playerPos.z);
	if (pos.Length() != 0.0f)
		drawPos_ = MAP_POSITION + pos.Normalized() * pos.Length() * ReSIZE;
	else
		drawPos_ = MAP_POSITION;

	/* 気流発生 */
	isDash = player->ReturnTackleParameter().dashFlag;
	if (isDash && isDash != prevDash)
		world.UIAdd(UI_ID::FLOWROOT_UI, std::make_shared<FlowRoot>(world, player, &drawPos_, resPiece));
	prevDash = isDash;
}

void PlayerArrow::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::MAP_PLAYER_SPRITE, drawPos_, Vector2(32, 32), 1.0f, Scale / 2.0f, angle_, true, false);
	Vector3 a = player->GetParameter().mat.GetPosition();
	DrawFormatString(0, 600, GetColor(255, 255, 255), "FPS:		[%f][%f][%f]", a.x, a.y, a.z);
}