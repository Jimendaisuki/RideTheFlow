#include "AnimTestActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../camera/Camera.h"
#include "../graphic/Anime.h"
#include "../time/Time.h"

AnimTestActor::AnimTestActor(IWorld& world) :
Actor(world),
position(Vector3(10,0,0)),
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
}
void AnimTestActor::Draw() const
{
	Anime::GetInstance().AttachAnime(MODEL_ID::TEST_MODEL, 0);
	Anime::GetInstance().PlayAnime(MODEL_ID::TEST_MODEL, 0, animetime*0.001f);
	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, Vector3::Zero);
}
void AnimTestActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}