#include "ActorManager.h"
#include "Actor.h"
#include<algorithm>

ActorManager::ActorManager(){

}

ActorManager::~ActorManager(){

}

void ActorManager::Update(){
	std::for_each(actorPtr.begin(), actorPtr.end(),
		[](ActorPtr actor){ actor->Update(); });
}

void ActorManager::Draw() const{
	std::for_each(actorPtr.begin(), actorPtr.end(),
		[](ActorPtr actor){
		actor->Draw();
	});
}

void ActorManager::Add(ActorPtr actor){
	actorPtr.push_back(actor);
}

void ActorManager::Clear(){
	actorPtr.clear();
}
void ActorManager::Remove(){
	actorPtr.remove_if([](ActorPtr actor){return actor->IsDead(); });
}
void ActorManager::Collide(Actor& other){
	std::for_each(actorPtr.begin(), actorPtr.end(),
		[&](ActorPtr actor){actor->Collide(other); });
}
void ActorManager::Collide(ActorManager& other){
	std::for_each(actorPtr.begin(), actorPtr.end(),
		[&](ActorPtr actor){other.Collide(*actor); });
}