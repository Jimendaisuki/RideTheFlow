#ifndef SHELL_BULLET_H_
#define SHELL_BULLET_H_

#include "../Actor.h"
#include <memory>

class ShellBullet :public Actor, public std::enable_shared_from_this<ShellBullet>
{
public:
	ShellBullet(IWorld& world, Vector3 position, Vector3 toPoint, Actor& parent);
	~ShellBullet();
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