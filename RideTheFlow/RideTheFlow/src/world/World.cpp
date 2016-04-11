#include "World.h"
#include "../actor/ActorID.h"

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

void World::Add(ActorPtr actor){
	actors.Add(ACTOR_ID::PLAYER, actor);
}

bool World::IsEnd()const{
	//‚Æ‚è‚ ‚¦‚¸
	return false;
}