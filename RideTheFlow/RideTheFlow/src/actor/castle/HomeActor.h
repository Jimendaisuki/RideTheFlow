#pragma once
#include "../Actor.h"
#include <vector>
#include <memory>

//è¸ÇËÇÃâ∆
class HomeActor :public Actor
{
public:
	HomeActor(IWorld& world, float scale,const Vector3& position_, const Vector3& rotate_);
	~HomeActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	
};