#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include "Tornado.h"

class TornadeBillboard :public Actor
{
public:
	TornadeBillboard(IWorld& world, Vector3& position_, std::weak_ptr<Tornado> tornade_);
	~TornadeBillboard();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 tornadePos;
	Vector3 tornadeMove;
	float tornadeAddRadius;
	float tornadeRadius;
	float tornadeSpeed;
	float tornadeDegree;
	float risingSpeed;
	float risingAddSpeed;

	float scale;
	Vector3 position;
	Vector3 rotate;

	Vector2 drawPosition;

	//âÒì]Ç…ÇÊÇ¡Çƒâ¡Ç¶ÇÁÇÍÇÈç¿ïWó 
	Vector3 tornadeAddPosition;
	float timer;
	int drawFrame;

	std::weak_ptr<Tornado> tornade;
};