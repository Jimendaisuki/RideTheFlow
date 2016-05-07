#pragma once

/* 当たり判定のテスト用 */

#include "Actor.h"
#include "../math/Vector3.h"
#include "Collision.h"
#include <memory>

class TestCapsule : public Actor, public std::enable_shared_from_this<TestCapsule>
{
public:
	TestCapsule(IWorld&  world, Vector3 position, bool isPlay);
	~TestCapsule();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
	bool	isPlay;
};



TestCapsule::TestCapsule(IWorld& world, Vector3 position_, bool	isPlay_) :
Actor(world),
position(position_),
isPlay(isPlay_)
{
	parameter.isDead = false;
	parameter.height = Vector3(0, 100, 0);
	parameter.mat =
		Matrix4::Translate(position);
}

TestCapsule::~TestCapsule()
{

}

void TestCapsule::Update()
{

	if (!isPlay) return;

	parameter.mat =
		Matrix4::Translate(position);
}

void TestCapsule::Draw() const
{
	DrawCapsule3D(parameter.mat.GetPosition, parameter.mat.GetPosition + parameter.height, parameter.radius, 8, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
}

void TestCapsule::OnCollide(Actor& other, CollisionParameter colpara)
{

}