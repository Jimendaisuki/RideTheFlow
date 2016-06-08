#pragma once
#include "../Actor.h"
#include <vector>
#include "../Player.h"
#include "ParticleSystem.h"

//É_ÉbÉVÉÖéûÇ…ê∂ê¨Ç∑ÇÈó¨ÇÍ
class Sand :public Actor, public ParticleSystem
{
public:
	//=======Actor======//
	Sand(IWorld& world, const Vector3& position_);
	~Sand();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	//=======ParticleSystem======//
	virtual void Emissive() override;

private:

};