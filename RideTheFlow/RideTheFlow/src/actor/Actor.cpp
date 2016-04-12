#include "Actor.h"

Actor::Actor()
{
	
}

Actor::~Actor(){

}

void Actor::Collide(Actor& other){
	if (IsCollide(other))
	{
		OnCollide(other);
		other.OnCollide(*this);
	}
}

bool Actor::IsCollide(const Actor& other) const
{
	return true;
}