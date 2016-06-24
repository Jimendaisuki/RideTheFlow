#pragma once
#include "Actor.h"
#include "../UIactor/CsvReader.h"
#include <string>

class StageGenerator : public Actor
{
public:
	StageGenerator(IWorld& world, const std::string& fileName);
	~StageGenerator();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	void DataLoad();
	void AddActor();

private:
	CsvReader	csv_;
	int			currentRow_;
};