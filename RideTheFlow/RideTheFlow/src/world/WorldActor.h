#pragma once
#include"../AllInclude.h"
#include "../actor/ActorPtr.h"
#include "../actor/ActorManager.h"
#include <map>

enum ACTOR_ID;

class WorldActor{
public:
	WorldActor();
	~WorldActor();
	void Update();
	void Draw() const;
	void Add(ACTOR_ID id, ActorPtr actor);
	void Clear();

private:
	typedef std::shared_ptr<ActorManager> ActorManagerPtr;
	typedef std::map<ACTOR_ID,ActorManagerPtr> ActorManagerPtrMap;
	typedef std::pair<ACTOR_ID, ActorManagerPtr> ActorManagerPair;
	ActorManagerPtrMap managers;
};