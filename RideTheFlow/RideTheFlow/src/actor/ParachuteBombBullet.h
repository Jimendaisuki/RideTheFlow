#ifndef PARACHUTE_BOMB_BULLET_H_
#define PARACHUTE_BOMB_BULLET_H_

#include"Actor.h"

class ParachuteBombBullet :public Actor
{
public:
	ParachuteBombBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, float height);
	~ParachuteBombBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Vector3 mPosition;
	Vector3 velocity;
	float initialVelocity;
	float mHeight;
	float time;
	bool HeightJuge;
};


#endif