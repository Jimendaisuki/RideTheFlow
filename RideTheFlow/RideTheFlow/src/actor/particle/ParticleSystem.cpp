#include "ParticleSystem.h"

#include "Particle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../graphic/TextDraw.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../math/Quaternion.h"

#include<algorithm>

ParticleSystem::ParticleSystem() 
{
	ps_parameter.isDead = false;
	ps_parameter.lifeTimeLimit = 5.0f;
	ps_parameter.intervalSec = 1.0f;
	ps_parameter.sameEmissiveNum = 1;
	ps_parameter.trigger = true;

	lifeTime = 0.0f;
	emissiveTimer = 0.0f;
	isTriggerEnd = false;
}

ParticleSystem::~ParticleSystem()
{
	particles.clear();
}

void ParticleSystem::UpdateParticles()
{
	//�������̕��o
	if (!isTriggerEnd && ps_parameter.trigger)
	{
		for (int i = 0; i < ps_parameter.sameEmissiveNum; i++)
		{
			Emissive();
		}
		isTriggerEnd = true;
	}

	//�V�X�e���̎����v�Z
	lifeTime += Time::GetInstance().deltaTime();
	if (lifeTime >= ps_parameter.lifeTimeLimit)
		ps_parameter.isDead = true;

	//�������s�����p�[�e�B�N�����폜
	RemoveDeadParticle();

	//�p�[�e�B�N�����X�V
	std::for_each(particles.begin(), particles.end(),
		[](ParticlePtr par){par->Update();
	});

	//���o
	emissiveTimer += Time::GetInstance().deltaTime();
	if (emissiveTimer > ps_parameter.intervalSec)
	{
		emissiveTimer = 0.0f;
		for (int i = 0; i < ps_parameter.sameEmissiveNum; i++)
		{
			Emissive();
		}
	}
}

void ParticleSystem::DrawParticles() const
{
	std::for_each(particles.begin(), particles.end(),
		[](ParticlePtr par){par->Draw(); });
}

void ParticleSystem::AddParticle(ParticlePtr particle)
{
	particles.push_back(particle);
}

void ParticleSystem::RemoveDeadParticle()
{
	particles.remove_if([](ParticlePtr par){return par->GetIsDead(); });
}

bool ParticleSystem::IsDeadSystem()
{
	return ps_parameter.isDead;
}