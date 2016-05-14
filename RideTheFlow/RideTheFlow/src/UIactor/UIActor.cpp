#include "UIActor.h"
#include "../world/IWorld.h"


UIActor::UIActor(IWorld& world_) : world(world_)
{

}

UIActor::~UIActor()
{

}

UIActorParameter UIActor::GetParameter() const
{
	return parameter;
}