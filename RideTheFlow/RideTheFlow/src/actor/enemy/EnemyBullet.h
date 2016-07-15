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

	//xz�i�s����
	Vector3 vec;
	//���f����]�l
	Vector3 rotate;

	//�����n
	Vector3 Tornadleft;
	bool isColTornad;
	bool isColFastFlag;

	float time;
	float speed;

	//�P�t���[���O�̍��W
	Vector3 prevPosition;
	//����Ƃ̃q�b�g���A����̌���
	Vector3 windVec;
	//����ƃq�b�g���Ă��邩�H
	bool isWindCol;

};
#endif