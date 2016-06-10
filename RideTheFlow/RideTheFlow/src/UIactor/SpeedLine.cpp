#include "SpeedLine.h"
#include "../Def.h"
#include "../game/Random.h"
#include "../math/Math.h"
#include "../time/Time.h"
#include <cmath>

// ���S���W
const Vector2 Center = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
// �ȉ~���a
const Vector2 Radius = Vector2(140.0f, 100.0f);

SpeedLine::SpeedLine(IWorld& world, float angle_) :
UIActor(world)
{
	parameter.isDead = false;
	parameter.id	 = UI_ID::SPEED_UI;

	/* �����ݒ� */
	alpha = 0.0f;
	alphaTime = 0.0f;
	speed = Random::GetInstance().Range(-3.0f, 3.0f);
	scale = Vector2(1.0f, abs(speed));

	/* �ʒu�E���͂��Z�o */
	position = Center + Vector2(Radius.x * Math::Cos(angle_), Radius.y * Math::Sin(angle_));
	velocity = Vector2::Normalize(position - Center);

	/* �p�x�̎Z�o */
	rotate = Math::Degree(Vector2::Right.Inner(velocity));
	/* ���������ɂ��␳ */
	int i = angle_ / 90;
	switch (i){
	case 2:		// ���� 180~269
		rotate = 360 - rotate;
		break;
	case 3:		// �E��	270~359
		rotate *= -1.0f;
		break;
	default:
		break;
	}
}

SpeedLine::SpeedLine(IWorld& world, float angle_, Vector3 position_) :
UIActor(world)
{
	parameter.isDead = false;
	parameter.id = UI_ID::SPEED_UI;

	/* �����ݒ� */
	alpha = 0.0f;
	alphaTime = 0.0f;
	speed = Random::GetInstance().Range(-3.0f, 3.0f);

	/* �ʒu�E���͂��Z�o */	 
	Vector2 screenPos = ConvWorldPosToScreenPos(position_.ToVECTOR());
	position = screenPos + Vector2(Radius.x * Math::Cos(angle_), Radius.y * Math::Sin(angle_));
	velocity = Vector2::Normalize(position - screenPos);

	/* ���S����̋����ɉ����ĕ␳ */
	float lengthRatio = Math::Clamp(Vector2::Distance(Center, position) / 100.0f, 0.8f, 1.5f);
	scale = Vector2(1.0f / lengthRatio, Random::GetInstance().Range(0.005f, 1.5f));
	speed *= lengthRatio;
	
	/* �o���ʒu���኱���S�ɖ߂� */
	position -= Vector2::Normalize(position - Center) * 15 * lengthRatio * lengthRatio;

	/* �p�x�̎Z�o */
	rotate = Math::Degree(Vector2::Right.Inner(velocity));
	/* ���������ɂ��␳ */
	int i = angle_ / 90;
	switch (i){
	case 2:		// ���� 180~269
		rotate = 360 - rotate;
		break;
	case 3:		// �E��	270~359
		rotate *= -1.0f;
		break;
	default:
		break;
	}
}

SpeedLine::SpeedLine(IWorld& world, Vector2 position_, Vector2 velocity_, float rotate_) :
UIActor(world),
velocity(velocity_),
rotate(rotate_)
{
	parameter.isDead = false;
	parameter.id = UI_ID::SPEED_UI;

	/* �����ݒ� */
	alpha = 0.0f;
	alphaTime = 0.0f;
	scale = Vector2(1.0f, Random::GetInstance().Range(0.1f, 3.0f) / 10.0f);
	speed = Random::GetInstance().Range(-5.0f, 10.0f);

	/* �ʒu���Z�o */
	if ((int)rotate % 180 == 0)	position = position_ + Vector2(Random::GetInstance().Range(-20.0f, 20.0f), 0.0f);
	else position = position_ + Vector2(0.0f, Random::GetInstance().Range(-20.0f, 20.0f));
}

SpeedLine::~SpeedLine()
{

}

void SpeedLine::Update()
{
	position += velocity * (1500 + 100 * speed) * Time::DeltaTime;

	alphaTime += Time::DeltaTime * (200 + 50 * speed);
	alpha = Math::Sin(alphaTime);
	if (alpha <= 0) parameter.isDead = true;
}

void SpeedLine::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPEED_SPRITE, position, Vector2(0, 16), alpha, scale, rotate, true, false);
}
