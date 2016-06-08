#ifndef SHIPENEMY_H_
#define SHIPENEMY_H_

#include "../Actor.h"
#include <memory>

struct ShipEnemyPos
{
	Vector3 spearPos;
	Vector3 varistorPosLeft;
	Vector3 varistorPosRight;
	Vector3 cannonPosLeft;
	Vector3 cannonPosRight;
};

class ShipEnemy :public Actor, public std::enable_shared_from_this<ShipEnemy>
{
public:
	ShipEnemy(IWorld& world, Vector3 position);
	~ShipEnemy();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;


private:
	void ShipEnemyPosition();
public :
	ShipEnemyPos GetShipEnemyPos()
	{
		return shipEnemyPos;
	}
	float getRotate()
	{
		return shipAngle;
	}
private:
	Vector3 mPosition;
	Vector3 rotate;
	Matrix4 playerMat;

	Vector3 coppyPos;
	Vector3 coppySpear;
	//çUåÇä÷åW
	float mSecondAttack;
	float mArrowNumber;
	float playerAngle;
	float attackTime;
	float attackRag;
	int arrowCount;
	bool isLook;


	float playerDot;
	float shipAngle;

	ShipEnemyPos shipEnemyPos;

};
#endif