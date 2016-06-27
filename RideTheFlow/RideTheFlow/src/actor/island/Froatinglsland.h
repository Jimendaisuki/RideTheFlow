#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>

class Froatinglsland : public Actor, public std::enable_shared_from_this<Froatinglsland>
{
public:
	Froatinglsland(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, bool isGameScene = true);
	~Froatinglsland();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	float timer;
	bool isCol;

	bool isGameScene;
};