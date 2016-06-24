#ifndef NOSHIPAREA_H_
#define NOSHIPAREA_H_

#include "Actor.h"
#include <memory>

class NoShipArea :public Actor, public std::enable_shared_from_this<NoShipArea>
{
public:
	NoShipArea(IWorld& world, Vector3 position,float radius, Actor& parent_);
	~NoShipArea();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Vector3 mPosition;
	float mRadius;
};
#endif