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
}

void World::Add(ACTOR_ID id, ActorPtr actor){
	actors.Add(id, actor);
}

void World::UIAdd(EFFECT_ID id, UIActorPtr actor){
	actors.EffectAdd(id, actor);
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
void World::EachUIActor(EFFECT_ID id, std::function<void(const UIActor&)> func)
{
	actors.EachUIActor(id, func);
}