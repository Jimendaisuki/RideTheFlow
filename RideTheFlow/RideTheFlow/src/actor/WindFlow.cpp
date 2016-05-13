#include "WindFlow.h"
#include "Collision.h"
#include <algorithm>


const int SplitNum = 5;
const float HeightMin = -100.0f;

WindFlow::WindFlow(IWorld& world, std::vector<Vector3>& positions_) :
Actor(world)
{
	parameter.isDead = false;

	int size = positions_.size();

	//–á‚Á‚Ä‚«‚½À•W”z—ñ‚ğ•ªŠ„‚µ‚Ä”z—ñ‚ÉŠi”[
	for (int i = 0; i < size; i++)
	{
		if (i % (size % SplitNum) == 0)
			positions.push_back(positions_.at(i));
	}
}
WindFlow::~WindFlow()
{

}
void WindFlow::Update()
{

}
void WindFlow::Draw() const
{

}
void WindFlow::OnCollide(Actor& other, CollisionParameter colpara)
{

}