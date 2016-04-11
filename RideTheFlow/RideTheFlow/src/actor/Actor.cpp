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
	return RCVector3::distance_(RCMatrix4::getPosition(parameter.matrix), RCMatrix4::getPosition(other.parameter.matrix)) <=
		parameter.radius + other.parameter.radius;
}