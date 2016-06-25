#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>

class Froatinglsland3 : public Actor, public std::enable_shared_from_this<Froatinglsland3>
{
public:
	Froatinglsland3(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale);
	~Froatinglsland3();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	float timer;
	bool isCol;
};