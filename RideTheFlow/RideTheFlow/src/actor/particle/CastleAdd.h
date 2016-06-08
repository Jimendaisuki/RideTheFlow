#pragma once
#include "../Actor.h"
#include <vector>
#include "../Player.h"
#include "ParticleSystem.h"

//城が増築するときにでるパーティクル
class CastleAdd :public Actor, public ParticleSystem
{
public:
	//=======Actor======//
	CastleAdd(IWorld& world, const Vector3& position_);
	~CastleAdd();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:

};