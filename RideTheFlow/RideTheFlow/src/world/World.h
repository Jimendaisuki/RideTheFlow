#pragma once
#include "../AllInclude.h"
#include "IWorld.h"
#include "WorldActor.h"

class World :public IWorld{
public:
	World();
	~World();

	void Initialize();
	void Update();
	void Draw() const;
	void Clear();
	virtual void Add(ACTOR_ID id, ActorPtr actor);
	virtual void Add(ActorPtr actor);
	virtual bool IsEnd() const;

private:
	WorldActor actors;
};