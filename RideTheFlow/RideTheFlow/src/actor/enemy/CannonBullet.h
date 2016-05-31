#ifndef SHELL_BULLET_H_
#define SHELL_BULLET_H_

#include "../Actor.h"
#include <memory>

class CannonBullet :public Actor, public std::enable_shared_from_this<CannonBullet>
{
public:
	CannonBullet(IWorld& world, Vector3 position, Actor& parent_, float rotateY, float attackAngleZ);
	~CannonBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 mRandomTarget;
	Vector3 mToPoint;
	Vector3 vec;
	float time;
	float speed;
	float mRotateY;
	float mRotateZ;

	//１フレーム前の座標
	Vector3 prevPosition;
	//流れとのヒット時、流れの向き
	Vector3 windVec;
	//流れとヒットしているか？
	bool isWindCol;
};
#endif