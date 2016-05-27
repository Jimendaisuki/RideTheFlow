#ifndef VARISTORBULLET_H_
#define VARISTORBULLET_H_

#include "../Actor.h"
#include <memory>

class VaristorBullet :public Actor, public std::enable_shared_from_this<VaristorBullet>
{
public:
	VaristorBullet(IWorld& world, Vector3 position, Vector3 toPoint, Actor& parent_);
	~VaristorBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 distance;
	Vector3 mRandomTarget;
	Vector3 coppyPosition;
	Vector3 mToPoint;
	Vector3 vec;
	float time;
	float speed;
};
#endif