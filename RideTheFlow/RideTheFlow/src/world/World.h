#pragma once
#include "IWorld.h"
#include "WorldActor.h"
#include "../UIactor/UIActor.h"

class World :public IWorld{
public:
	World();
	~World();

	void Initialize();
	void Update();
	void Draw() const;
	void Clear();
	virtual void Add(ACTOR_ID id, ActorPtr actor);
	virtual void UIAdd(EFFECT_ID id, UIActorPtr UIactor);
	virtual bool IsEnd() const;
	virtual void SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID);

	//子オブジェクトを巡回
	virtual void EachActor(ACTOR_ID id, std::function<void(const Actor&)> func) override;
	virtual void EachUIActor(EFFECT_ID id, std::function<void(const UIActor&)> func) override;

	virtual ActorPtr GetPlayer() const override;
	virtual ActorPtr GetCamera() const override;

private:
	WorldActor actors;
	ActorPtr   playerActor, cameraActor;
};