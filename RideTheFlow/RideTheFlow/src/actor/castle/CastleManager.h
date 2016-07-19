#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include  <vector>
#include<memory>
#include "../ActorPtr.h"

class CastleManager : public Actor
{
public:
	CastleManager(IWorld& world);
	~CastleManager();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	float rankUpTimer;
	float spawnArmyTimer;
	float spawnShipTimer;
};