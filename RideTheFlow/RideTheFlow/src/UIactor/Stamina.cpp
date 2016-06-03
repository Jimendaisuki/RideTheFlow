#include "Stamina.h"
#include "../math/Math.h"
#include "../Def.h"
#include "../actor/Actor.h"
#include "../world/IWorld.h"

#include "../input/Keyboard.h"

const Vector2 HD = Vector2(1920, 1080);
const Vector2 resSize = Vector2(1625, 125);
const Vector2 DrawPosition = Vector2(100, 0);
Stamina::Stamina(IWorld& world, float& maxStamina_, float& nowStamina_) :
UIActor(world)
{
	/* �����ݒ� */
	parameter.isDead = false;
	parameter.id = EFFECT_ID::STAMINA_EFFECT;
	scale.x = (float)WINDOW_WIDTH  / HD.x;
	scale.y = (float)WINDOW_HEIGHT / HD.y;

	/* ��������|�C���^�Q�� */
	maxStamina = &maxStamina_;
	nowStamina = &nowStamina_;
}

Stamina::~Stamina()
{
	// �|�C���^���
	maxStamina = nullptr;
	nowStamina = nullptr;
}

void Stamina::Update()
{	
	// �ꉞ�N�����v����
	*nowStamina = Math::Clamp(*nowStamina, 0.0f, *maxStamina);
}

void Stamina::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::STAMINA_BACK_SPRITE , DrawPosition, Vector2::Zero, 1, scale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::STAMINA_SPRITE, DrawPosition, Point(resSize.x * (*nowStamina / *maxStamina), resSize.y), Vector2::Zero, 1, scale, 0, true, false);
}