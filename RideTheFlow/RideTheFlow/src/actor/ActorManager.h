#pragma once
#include "../AllInclude.h"

#include"ActorPtr.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include<list>//シーケンスコンテナlistを実装する
#include <functional>
#include "ID.h"
class ActorManager
{
public:
	ActorManager();
	~ActorManager();
	void Update();
	void Draw() const;
	void Add(ActorPtr actor);
	void Clear();
	void Remove();
	void Collide(COL_ID id, Actor& other);
	void Collide(COL_ID id, ActorManager& other);

	//子を巡回
	void EachActor(std::function<void(Actor&)> func);

	std::list<ActorPtr> getlist();
private:
	std::list<ActorPtr> actorPtr;
};