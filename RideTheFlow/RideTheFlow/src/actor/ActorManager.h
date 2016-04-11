#pragma once
#include "../AllInclude.h"

#include"ActorPtr.h"
#include<list>//シーケンスコンテナlistを実装する
#include <functional>
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
	void Collide(Actor& other);
	void Collide(ActorManager& other);
private:
	std::list<ActorPtr> actorPtr;
};