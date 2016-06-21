#pragma once
#include "../Actor.h"
#include <vector>
#include "../Player.h"
#include "ParticleSystem.h"

//âÛÇÍÇÈèÈÇëIë
enum CASTLE_SELECT
{
	MASTER_CASTLE,
	CHILD_CASTLE,
};

class BreakCastle :public Actor, public ParticleSystem
{
public:
	//=======Actor======//
	BreakCastle(IWorld& world, const Vector3& position_, const CASTLE_SELECT& select);
	~BreakCastle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:
	float rotX, rotY;
};