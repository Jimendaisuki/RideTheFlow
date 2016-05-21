#include "Blood.h"
#include "../game/Random.h"
#include "../math/Math.h"
#include "../time/Time.h"
#include "../Def.h"
#include "../world/IWorld.h"

/*
�ǉ����@����
EnemuBullet.h
EnemyBullet(IWorld& world, Vector3 position, Actor& parent_);
.cpp
EnemyBullet::EnemyBullet(IWorld& world, Vector3 position, Actor& parent_) : 
parent = &parent_;

�o���b�g�������Ă���A�N�^�[
world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, *this));


OnCollisin��
�v���C���[�̏ꍇ
Effect::GetInstance().DamegeEffect(world, other.parent->GetParameter().mat.GetPosition());
�o���b�g�̏ꍇ
Effect::GetInstance().DamegeEffect(world, parent->GetParameter().mat.GetPosition());
*/

const float deadTime = 2.0f;
const float offset = 20.0f;

// ���S���W
const Vector2 Center = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
// �ȉ~���a
const Vector2 Radius = Vector2(400.0f, 300.0f);

Blood::Blood(IWorld& world, const Vector3 position_) :
UIActor(world)
{
	parameter.isDead = false;
	parameter.id	 = EFFECT_ID::BLOOD_EFFECT;

	/* �����ݒ� */
	alpha     = 1.0f;
	alphaTime = deadTime;
	scale  = Vector2(0.5f) * Random::GetInstance().Range(0.5f, 1.5f);
	rotate = Random::GetInstance().Range(0.0f, 359.0f);

	/* �ʒu���Z�o */
	Vector3 temp = ConvWorldPosToScreenPos(position_.ToVECTOR());
	position = Vector2(
		Math::Clamp(temp.x, offset, (float)WINDOW_WIDTH - offset) + Random::GetInstance().Range(-20.0f, 20.0f),
		Math::Clamp(temp.y, offset, (float)WINDOW_HEIGHT - offset) + Random::GetInstance().Range(-20.0f, 20.0f));
	
	/* �J�����̗����ɂ����ꍇ�̕␳ */
	if (temp.z >= 1)
	{
		position.x = (WINDOW_WIDTH - position.x) + Random::GetInstance().Range(-20.0f, 20.0f);
		position.y = WINDOW_HEIGHT + Random::GetInstance().Range(-20.0f, 20.0f);
	}
}

Blood::Blood(IWorld& world_, const Vector3 position_, const Actor& player_) :
UIActor(world_)
{
	parameter.isDead = false;
	parameter.id = EFFECT_ID::BLOOD_EFFECT;

	/* �����ݒ� */
	alpha = 1.0f;
	alphaTime = deadTime;
	scale = Vector2(0.5f) * Random::GetInstance().Range(0.5f, 1.5f);
	rotate = Random::GetInstance().Range(0.0f, 359.0f);

	/* �J�����ʒu�擾 */
	Vector3 cameraPos;
	world.EachActor(ACTOR_ID::CAMERA_ACTOR, [&](const Actor& other){
		cameraPos = other.GetParameter().mat.GetPosition();
	});

	/* �J��������̊e��x�N�g�� */
	Vector3 C_to_Pvec = player_.GetParameter().mat.GetPosition() - cameraPos;
	Vector3 C_to_Evec = position_ - cameraPos;
	/* �Ȃ��p */
	float angle = Math::Degree(Vector2::Inner(Vector2(C_to_Pvec.x, C_to_Pvec.z).Normalized(), Vector2(C_to_Evec.x, C_to_Evec.z).Normalized()));

	/* �E������ */
	Vector2 Normal = Vector2(-C_to_Pvec.z, C_to_Pvec.x).Normalized();
	float dot = Vector2::Dot(Normal, Vector2(C_to_Evec.x, C_to_Evec.z));
	if (dot <= 0) position = Center + Vector2(Radius.x * Math::Sin(angle), Radius.y * Math::Cos(180.0f - angle));
	else position = Center + Vector2(-Radius.x * Math::Sin(angle), Radius.y * Math::Cos(180.0f - angle));

	/* �Ō�Ɋe���炷 */
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