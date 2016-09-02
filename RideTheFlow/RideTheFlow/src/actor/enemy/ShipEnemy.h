#ifndef SHIPENEMY_H_
#define SHIPENEMY_H_

#include "../Actor.h"
#include <memory>
#include "../particle/BreakCastle.h"

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
	ShipEnemy(IWorld& world, float scale, const Vector3& position_, const Vector3& rotate_);
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
	Vector3 isLandPos;
	ShipEnemyPos shipEnemyPos;
	//ìßñæìx
	float alpha;
	//çUåÇä÷åW
	float mSecondAttack;
	float mArrowNumber;
	float playerAngle;
	float attackTime;
	float attackRag;
	float playerDot;
	int arrowCount;
	bool isLook;

	//ïÇóVìáä÷åW
	float isLandDot;
	float shipAngle;
	float shipLow;
	bool isLandCol;

	//ñ≥ìGä÷åW
	float invincibleTimer;
	bool damege;

	bool isTitle;

	//éÄàˆ
	BREAK_SELECT breakSelect;
};
#endif