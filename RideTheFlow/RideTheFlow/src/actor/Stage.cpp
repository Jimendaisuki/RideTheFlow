#include "Stage.h"
#include "Collision.h"
#include "../graphic/Model.h"

Stage::Stage(IWorld& world) :
Actor(world){
	parameter.isDead = false;
}
Stage::~Stage(){

}

void Stage::Update(){

}
void Stage::Draw() const{
	Model::GetInstance().Draw(MODEL_ID::STAGE_MODEL, Vector3(0, -100, 0), 1.0f, Vector3::Zero, Vector3(1));
}

void Stage::OnCollide(Actor& other, CollisionParameter colpara){

}