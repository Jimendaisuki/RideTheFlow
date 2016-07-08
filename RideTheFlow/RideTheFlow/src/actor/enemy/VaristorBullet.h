#ifndef VARISTORBULLET_H_
#define VARISTORBULLET_H_

#include "../Actor.h"
#include <memory>

class VaristorBullet :public Actor, public std::enable_shared_from_this<VaristorBullet>
{
public:
	VaristorBullet(IWorld& world, Vector3 position, Actor& parent_, float rotateY, float attackAngleZ,float InitialVec);
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
	Vector3 seveVec;
	Vector3 vec;
	float mRotateY;
	float mRotateZ;
	float noDeadTimer;
	float noDead;
	float mInitialVec;

	//１フレーム前の座標
	Vector3 prevPosition;
	//流れとのヒット時、流れの向き
	Vector3 windVec;
	//流れとヒットしているか？
	bool isWindCol;

	float time;
	float speed;
};
#endif