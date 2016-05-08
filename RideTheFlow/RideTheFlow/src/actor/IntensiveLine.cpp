#include "IntensiveLine.h"
#include "Collision.h"
#include "../Def.h"
#include "../game/Random.h"
#include "../graphic/Model.h"
#include "../graphic/BlendMode.h"
#include "../math/Math.h"
#include "../time/Time.h"

// ���S���W
Vector2 Center = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
// �ȉ~���a
Vector2 Radius = Vector2(140.0f, 100.0f);

IntensiveLine::IntensiveLine(IWorld& world, float angle_) :
Actor(world)
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::INTENSIVELINE_ACTOR;

	/* �����ݒ� */
	alpha = 0.0f;
	alphaTime = 0.0f;
	speed = Random::GetInstance().Range(-3.0f, 3.0f);

	/* �ʒu�E���͂��Z�o */
	position = Center + Vector2(Radius.x * Math::Cos(angle_), Radius.y * Math::Sin(angle_));
	velocity = Vector2::Normalize(position - Center);

	/* �p�x�̎Z�o */
	rotate = Math::Degree(Vector2::Right.Inner(velocity));
	/* ���������ɂ��␳ */
	int i = angle_ / 90;
	switch (i){
	case 2:
		rotate = 360 - rotate;
		break;
	case 3:
		rotate *= -1.0f;
		break;
	default:
		break;
	}
}

IntensiveLine::~IntensiveLine()
{

}

void  IntensiveLine::Update()
{
	position += velocity * (1500 + 100 * speed) * Time::DeltaTime;

	alphaTime += Time::DeltaTime * (200 + 50 * speed);
	alpha = Math::Sin(alphaTime);
	if (alpha <= 0) parameter.isDead = true;
}

void IntensiveLine::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::INTENSIVELINE_SPRITE, position, Vector2(0, 16), alpha, Vector2(1.0f, abs(speed)), rotate, true, false);
}

void IntensiveLine::OnCollide(Actor& other, CollisionParameter colpara){}