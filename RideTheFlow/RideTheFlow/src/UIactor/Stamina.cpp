#include "Stamina.h"
#include "../math/Math.h"
#include "../world/IWorld.h"

const Vector2 HD = Vector2(1920, 1080);
const Vector2 resSize = Vector2(1625, 125);
const float	  offset = resSize.x - 1530.0f;
const float	  gageX = resSize.x - offset;
const Vector2 DrawPosition = Vector2(100, 0);
Stamina::Stamina(IWorld& world, float& maxStamina_, float& nowStamina_, Player& player_) :
UIActor(world)
{
	/* 初期設定 */
	parameter.isDead = false;
	parameter.id = UI_ID::STAMINA_UI;
	scale.x = (float)WINDOW_WIDTH  / HD.x;
	scale.y = (float)WINDOW_HEIGHT / HD.y;

	player = &player_;

	/* 引数からポインタ参照 */
	maxStamina = &maxStamina_;
	nowStamina = &nowStamina_;

}

Stamina::~Stamina()
{
	// ポインタ解放
	maxStamina = nullptr;
	nowStamina = nullptr;
}

void Stamina::Update()
{	
	// 一応クランプ処理
	*nowStamina = Math::Clamp(*nowStamina, 0.0f, *maxStamina);
}

void Stamina::Draw() const
{
	float gageColorNum = 255.0f * ((*maxStamina - *nowStamina) / *maxStamina);
	SetDrawBright(255.0f, gageColorNum, gageColorNum);
	if (player->OverHeat())
		SetDrawBright(255, 0, 0);
	Sprite::GetInstance().Draw(SPRITE_ID::STAMINA_BACK_SPRITE , DrawPosition, Vector2::Zero, 1, scale, true, false);
	SetDrawBright(255, 255, 255);
	Sprite::GetInstance().Draw(SPRITE_ID::STAMINA_SPRITE, DrawPosition, Point(offset / 2.0f + gageX * (((*maxStamina - *nowStamina) / *maxStamina)), resSize.y), Vector2::Zero, 1, scale, 0, true, false);
}