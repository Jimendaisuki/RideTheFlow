#include "Tornado.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../math/Math.h"

Tornado::Tornado(IWorld& world, Vector3 position, Vector3 velocity) :
Actor(world),
position(position),
velocity(velocity),
scale(Vector3(1.0f, 1.0f, 1.0f))
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	parameter.radius = 10.0f;
}

Tornado::~Tornado()
{

}

void Tornado::Update()
{
	position += velocity * Time::DeltaTime;
	rotate.y += 1000 * Time::DeltaTime;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);

	scale -= Vector3(0.1f * Time::DeltaTime, 0.0f, 0.1f * Time::DeltaTime);
	if (scale.x + scale.z <= 0.2f)
	{
		world.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(world, Vector3(0, -50, 0), Vector3(10, 0, 0)));
		parameter.isDead = true;
	}
}

void Tornado::Draw() const
{
	// プレイヤー描画情報を流用
	Model::GetInstance().Draw(MODEL_ID::TORNADO_MODEL, Matrix4::GetPosition(parameter.mat), rotate, scale);
	//Sprite::GetInstance().Draw(SPRITE_ID::PLAYER_SPRITE, Vector2(-150, -150), 0.5f);
	DrawSphere3D(Matrix4::GetPosition(parameter.mat), parameter.radius, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

void Tornado::OnCollide(Actor& other, CollisionParameter colpara)
{

}