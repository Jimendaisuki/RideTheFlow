#include "AnimTestActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../graphic/Anime.h"
#include "../time/Time.h"

AnimTestActor::AnimTestActor(IWorld& world) :
Actor(world),
position(Vector3::Zero),
animetime(0.0f)
{
	parameter.isDead = false;
}
AnimTestActor::~AnimTestActor()
{

}
void AnimTestActor::Update()
{
	animetime += Time::DeltaTime;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		position.x -= 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		position.x += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		position.z += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		position.z -= 100.0f * Time::DeltaTime;

	parameter.mat =
		Matrix4::Scale(Vector3(1, 1, 1)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
}
void AnimTestActor::Draw() const
{
	Anime::GetInstance().AttachAnime(MODEL_ID::TEST_MODEL, 0);
	Anime::GetInstance().PlayAnime(MODEL_ID::TEST_MODEL, 0, animetime*0.001f);
	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, parameter.mat.GetPosition());
}
void AnimTestActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}