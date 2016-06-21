#include "Stage.h"
#include "Collision.h"
#include "../graphic/Model.h"

static const int MODEL_SIZE = 45;

Stage::Stage(IWorld& world) :
Actor(world){
	parameter.isDead = false;
}
Stage::~Stage(){

}

void Stage::Update(){

}
void Stage::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::TEST_STAGE, Vector3(0, -600, 0), 1.0f, Vector3::Zero, Vector3(MODEL_SIZE));
	Model::GetInstance().Draw(MODEL_ID::SKY_MODEL, Vector3(0, 0, 0), 1.0f, Vector3::Zero, Vector3(MODEL_SIZE));
	Model::GetInstance().Draw(MODEL_ID::STAGE_ACTION_RANGE_MODEL, Vector3(0, -400, 0), 1.0f, Vector3::Zero, Vector3(MODEL_SIZE, MODEL_SIZE, MODEL_SIZE));
}

void Stage::OnCollide(Actor& other, CollisionParameter colpara){

}