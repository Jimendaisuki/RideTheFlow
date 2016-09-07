#pragma once
#include "../AllInclude.h"
#include "../Def.h"
#include "../actor/ID.h"
#include "../graphic/Sprite.h"
#include <map>
#include <functional>

class IWorld;

struct UIActorParameter
{
	UI_ID id;
	bool isDead;
};

class UIActor{
public:
	UIActor(IWorld& world_);
	virtual ~UIActor();
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual bool IsDead() const{ return parameter.isDead; }
	UIActorParameter GetParameter() const;

protected:
	UIActorParameter parameter;
	IWorld& world;
};