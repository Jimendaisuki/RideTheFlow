#include "World.h"
#include "../actor/ID.h"

World::World(){

}

World::~World(){
	Clear();
}

void World::Initialize(){
	Clear();
}
void World::Update(){
	actors.Update();
}
void World::Draw() const{
	actors.Draw();
}
void World::Clear(){
	actors.Clear();
	playerActor = nullptr;
	cameraActor = nullptr;
	masterCastles.clear();
}

void World::Add(ACTOR_ID id, ActorPtr actor){
	if (id == ACTOR_ID::PLAYER_ACTOR)		playerActor = actor;
	else if (id == ACTOR_ID::CAMERA_ACTOR)	cameraActor = actor;
	else if (id == ACTOR_ID::MASTER_CASTLE_ACTOR)	masterCastles.push_back(actor);
	actors.Add(id, actor);
}

void World::UIAdd(UI_ID id, UIActorPtr actor){
	actors.UIAdd(id, actor);
}

bool World::IsEnd()const{
	//とりあえず
	return false;
}

void World::SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID){
	actors.SetCollideSelect(thisActor, otherID, colID);
}

//子オブジェクトを巡回
void World::EachActor(ACTOR_ID id, std::function<void(const Actor&)> func)
{
	actors.EachActor(id, func);
}
void World::EachUIActor(UI_ID id, std::function<void(const UIActor&)> func)
{
	actors.EachUIActor(id, func);
}

ActorPtr World::GetPlayer() const
{
	return playerActor;
}


ActorPtr World::GetCamera() const
{
	return cameraActor;
}
std::vector<ActorPtr> World::GetMasterCastle() const
{
	return masterCastles;
}
int World::GetActorCount(ACTOR_ID id,ACTOR_ID id2)
{
	int count = actors.GetActorCount(id,id2);
	return count;
}