#include "castle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"

Castle::Castle(IWorld& world, Vector3 position) :
Actor(world),
position(position)
{
	parameter.isDead = false;
}

Castle::~Castle()
{

}

void Castle::Update()
{

}

void Castle::Draw() const
{
	// プレイヤー描画情報を流用
	Model::GetInstance().Draw(MODEL_ID::TORNADO_MODEL, position);
	//Sprite::GetInstance().Draw(SPRITE_ID::PLAYER_SPRITE, Vector2(-150, -150), 0.5f);
}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{

}