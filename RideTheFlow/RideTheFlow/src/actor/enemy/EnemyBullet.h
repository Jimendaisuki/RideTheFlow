#ifndef ENEMY_VARISTOR_BULLET_H_
#define ENEMY_VARISTOR_BULLET_H_

#include "../Actor.h"
#include <memory>

class EnemyBullet :public Actor, public std::enable_shared_from_this<EnemyBullet>
{
public:
	EnemyBullet(IWorld& world, Vector3 position,Vector3 toPoint, Actor& parent_);
	~EnemyBullet();
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

	float noDeadTimer;
	float noDead;

	//xz進行方向
	Vector3 vec;
	//モデル回転値
	Vector3 rotate;

	//竜巻系
	Vector3 Tornadleft;
	bool isColTornad;
	bool isColFastFlag;

	float time;
	float speed;

	//１フレーム前の座標
	Vector3 prevPosition;
	//流れとのヒット時、流れの向き
	Vector3 windVec;
	//流れとヒットしているか？
	bool isWindCol;

};
#endif