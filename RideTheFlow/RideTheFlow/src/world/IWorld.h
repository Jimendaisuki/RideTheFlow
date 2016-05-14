#pragma once
#include "../actor/ActorPtr.h"
#include "../UIactor/UIActorPtr.h"
#include <functional>
enum ACTOR_ID;
enum COL_ID;
enum EFFECT_ID;

class IWorld{
public:
	virtual ~IWorld(){}
	virtual void Add(ACTOR_ID id, ActorPtr actor) = 0;
	virtual void UIAdd(EFFECT_ID id, UIActorPtr UIactor) = 0;
	virtual bool IsEnd()const = 0;
	virtual void SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID) = 0;

	//子オブジェクトを巡回
	virtual void EachActor(ACTOR_ID id, std::function<void(const Actor&)> func) = 0;
	virtual void EachUIActor(EFFECT_ID id, std::function<void(const UIActor&)> func) = 0;
};