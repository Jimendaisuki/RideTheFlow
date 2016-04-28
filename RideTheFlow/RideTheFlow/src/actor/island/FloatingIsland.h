#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>

class FroatingIsland : public Actor, public std::enable_shared_from_this<FroatingIsland>
{
public:
	FroatingIsland(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale);
	~FroatingIsland();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	float HP;
};