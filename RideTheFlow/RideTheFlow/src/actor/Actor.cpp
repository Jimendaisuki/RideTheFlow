#include "Actor.h"
#include "Collision.h"
#include "../world/IWorld.h"


Actor::Actor(IWorld& world_) :world(world_)
{
	colFunc[COL_ID::SPHERE_SPHERE_COL] = std::bind(&Actor::SphereSphere, this, std::placeholders::_1);
}

Actor::~Actor(){

}

void Actor::Collide(COL_ID id, Actor& other){
	CollisionParameter colpara = colFunc[id](other);
	if (colpara.colFlag)
	{
		OnCollide(other, colpara);
		other.OnCollide(*this, colpara);
	}
}

//‹…‚Æ‹…‚Ì‚ ‚½‚è”»’è
CollisionParameter Actor::SphereSphere(const Actor& other) const{
	CollisionParameter colpara;
	return colpara;
}

ActorParameter Actor::GetParameter()
{
	return parameter;
}