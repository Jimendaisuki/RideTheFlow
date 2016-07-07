#include "Stage.h"
#include "Collision.h"
#include "../graphic/Model.h"

static const int MODEL_SIZE = 240;

Stage::Stage(IWorld& world) :
Actor(world){
	parameter.isDead = false;
}
Stage::~Stage(){
	parent = nullptr;
}

void Stage::Update(){

}
void Stage::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::TEST_STAGE, Vector3(0, -3600, 0), Vector3::Zero, Vector3(MODEL_SIZE));
	Model::GetInstance().Draw(MODEL_ID::SKY_MODEL, Vector3(0, 0, 0), Vector3::Zero, Vector3(MODEL_SIZE / 2));
	Model::GetInstance().Draw(MODEL_ID::STAGE_ACTION_RANGE_MODEL, Vector3(0, -2400, 0), Vector3::Zero, Vector3(MODEL_SIZE));
}

void Stage::OnCollide(Actor& other, CollisionParameter colpara){

}