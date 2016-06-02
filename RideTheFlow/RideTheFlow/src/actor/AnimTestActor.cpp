#include "AnimTestActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../graphic/Anime.h"
#include "../time/Time.h"
#include "../graphic/TextDraw.h"

AnimTestActor::AnimTestActor(IWorld& world) :
Actor(world),
position(Vector3::Zero),
rotate(Vector3::Zero),
animetime(0.0f)
{
	parameter.isDead = false;

	//Anime::GetInstance().AttachAnime(MODEL_ID::TEST_MODEL, 0);
}
AnimTestActor::~AnimTestActor()
{

}
void AnimTestActor::Update()
{
	animetime += 10.0f * Time::DeltaTime;
	if (animetime > 140.0f)
	{
		animetime = 0.0f;
	}

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		position.x -= 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		position.x += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		position.z += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		position.z -= 100.0f * Time::DeltaTime;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::NUM1))
		rotate.x += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::NUM2))
		rotate.x -= 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::NUM3))
		rotate.y += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::NUM4))
		rotate.y -= 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::NUM5))
		rotate.z += 100.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::NUM6))
		rotate.z -= 100.0f * Time::DeltaTime;

	parameter.mat = 
		Matrix4::Scale(Vector3::One) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::Translate(position);
}
void AnimTestActor::Draw() const
{
	//Anime::GetInstance().PlayAnime(MODEL_ID::TEST_MODEL, 0, animetime);
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat);

	TextDraw::Draw(Vector3(animetime * 6.0f));
	TextDraw::Draw(Point(0, 20), parameter.mat.GetRotate());
	//TextDraw::Draw(Point(0, 40), parameter.mat);
}
void AnimTestActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}