#include "NoShipArea.h"
#include "Collision.h"
#include "castle\castle.h"
NoShipArea::NoShipArea(IWorld& world, Vector3 position,float radius, Actor& _parent) :
Actor(world)
{
	parameter.isDead = false;
	parameter.radius = radius;

	parameter.mat = Matrix4::Translate(position);

	mPosition = position;
	mRadius = radius;
	parent = &_parent;
}


NoShipArea::~NoShipArea()
{

}

void NoShipArea::Update()
{
	if (parent->GetParameter().id==ACTOR_ID::CASTLE_ACTOR)
	mPosition = parent->GetParameter().mat.GetPosition() + Vector3(0.0f, parent->GetParameter().radius,0.0f);

	if (parent->GetParameter().isDead)
		parameter.isDead = true;

	parameter.mat = Matrix4::Translate(mPosition);
}

void NoShipArea::Draw() const
{
}

void NoShipArea::OnCollide(Actor& other, CollisionParameter colpara)
{
}