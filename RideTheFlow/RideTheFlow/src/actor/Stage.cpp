#include "Stage.h"
#include "Collision.h"
#include "../graphic/Model.h"

Stage::Stage(IWorld& world) :
Actor(world){
	parameter.isDead = false;
	VertexShaderHandle = LoadVertexShader("res/NormalMesh_DirLight_NrmMapVS.vso");
	PixelShaderHandle = LoadPixelShader("res/NormalMesh_DirLight_NrmMapPS.pso");
	SetUseVertexShader(VertexShaderHandle);
	SetUsePixelShader(PixelShaderHandle);
}
Stage::~Stage(){

}

void Stage::Update(){

}
void Stage::Draw() const{
	MV1SetUseOrigShader(TRUE);
	Model::GetInstance().Draw(MODEL_ID::TEST_STAGE, Vector3(0, -400, 0), 1.0f, Vector3::Zero, Vector3(30));
	MV1SetUseOrigShader(FALSE);
	Model::GetInstance().Draw(MODEL_ID::SKY_MODEL, Vector3(0, 0, 0), 1.0f, Vector3::Zero, Vector3(30));
	Model::GetInstance().Draw(MODEL_ID::STAGE_ACTION_RANGE_MODEL, Vector3(0, -400, 0), 1.0f, Vector3::Zero, Vector3(30, 34, 30));
}

void Stage::OnCollide(Actor& other, CollisionParameter colpara){

}