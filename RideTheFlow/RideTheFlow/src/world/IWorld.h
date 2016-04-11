#pragma once
#include "../actor/ActorPtr.h"
enum ACTOR_ID;

class IWorld{
public:
	virtual ~IWorld(){}
	virtual void Add(ACTOR_ID id, ActorPtr actor) = 0;
	virtual void Add(ActorPtr actor) = 0;
	virtual bool IsEnd()const = 0;
};