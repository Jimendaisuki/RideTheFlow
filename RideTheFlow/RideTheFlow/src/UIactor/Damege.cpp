#include "Damege.h"
#include "../math/Math.h"
#include "../Def.h"
#include "../actor/Actor.h"
#include "../world/IWorld.h"

#include "../input/Keyboard.h"

const float deadTime = 2.0f;
const float offset = 20.0f;
const Vector2 resSize = Vector2(1920, 1080);
Damege::Damege(IWorld& world) :
UIActor(world)
{
	parameter.isDead = false;
	parameter.id = EFFECT_ID::DAMAGE_EFFECT;

	/* 初期設定 */
	scale.x = (float)WINDOW_WIDTH / resSize.x;
	scale.y = (float)WINDOW_HEIGHT / resSize.y;

	/* プレイヤーのHPを取得 */
	//world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other)
	//{
	//	maxHP = other.parameter.HP;
	//	nowHP = maxHP;
	//});

	maxHP = 50;
	nowHP = maxHP;

}

Damege::~Damege()
{

}

void Damege::Update()
{
	/* プレイヤーのHPを取得 */
	//world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other)
	//{
	//	nowHP = other.parameter.HP;
	//});

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::R)){
		nowHP++;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::F)){
		nowHP--;
	}

}

void Damege::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::DAMEGE_SPRITE, Vector2::Zero, Vector2::Zero, 1.0f - Math::Clamp(nowHP / maxHP, 0.0f, 1.0f), scale, 0.0f, true, false);
}