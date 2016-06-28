#include "WorldActor.h"
#include<algorithm>
#include "../actor/ID.h"
#include <algorithm>
#include "../actor/Actor.h"
#include "../actor/ActorPtr.h"

WorldActor::WorldActor(){
	for (int i = ACTOR_ID::BEGIN_ACTOR; i <= ACTOR_ID::END_ACTOR; ++i)
		managers.emplace(ACTOR_ID(i), std::make_shared<ActorManager>());
	for (int i = UI_ID::BEGIN_UI; i <= UI_ID::END_UI; ++i)
		UImanagers.emplace(UI_ID(i), std::make_shared<UIActorManager>());
}
WorldActor::~WorldActor(){

}
void WorldActor::Update(){
	//全キャラアップデート
	std::for_each(managers.begin(), managers.end(),
		[&](ActorManagerPair pair){pair.second->Update(); });
	//全エフェクトアップデート
	std::for_each(UImanagers.begin(), UImanagers.end(),
		[&](UIActorManagerPair UIpair){UIpair.second->Update(); });

	//あたり判定
	for (auto& cols : colselect){
		for (auto& sec : cols.second){
			managers[sec.otherID]->Collide(sec.colID, *cols.first);
		}
	}

	colselect.clear();
	//死んでるものを消す
	std::for_each(managers.begin(), managers.end(),
		[](ActorManagerPair pair){pair.second->Remove(); });
	std::for_each(UImanagers.begin(), UImanagers.end(),
		[](UIActorManagerPair UIpair){UIpair.second->Remove(); });
}
void WorldActor::Draw() const{
	//全キャラ描画
	std::for_each(managers.begin(), managers.end(),
		[&](ActorManagerPair pair){pair.second->Draw(); });

	//全エフェクト描画
	std::for_each(UImanagers.begin(), UImanagers.end(),
		[&](UIActorManagerPair UIpair){UIpair.second->Draw(); });
}
void WorldActor::Add(ACTOR_ID id, ActorPtr actor){
	managers[id]->Add(actor);
}

void WorldActor::UIAdd(UI_ID id, UIActorPtr UIactor){
	UImanagers[id]->Add(UIactor);
}
void WorldActor::Clear(){
	//全キャラクリア
	std::for_each(managers.begin(), managers.end(),
		[](ActorManagerPair pair){pair.second->Clear(); });
	//全エフェクトクリア
	std::for_each(UImanagers.begin(), UImanagers.end(),
		[](UIActorManagerPair UIpair){UIpair.second->Clear(); });
}

void WorldActor::SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID){
	CollideSelect c = { otherID, colID };
	colselect[thisActor].push_back(c);
}

//子を巡回
void WorldActor::EachActor(ACTOR_ID id, std::function<void(const Actor&)> func)
{
	managers[id]->EachActor(func);
}
void WorldActor::EachUIActor(UI_ID id, std::function<void(const UIActor&)> func)
{
	UImanagers[id]->EachActor(func);
}
int WorldActor::GetActorCount(ACTOR_ID id, ACTOR_ID id2)
{
	int count = 0;
	if (managers[id]->getlist().size() < 1)return 0;

	for (auto i : managers[id]->getlist()){
		if (i->GetParameter().id ==id2 )
			count++;
	}
	return count;
}
std::vector<ActorPtr> WorldActor::GetActors(ACTOR_ID id)
{
	std::vector<ActorPtr> masters;
	if (managers[id]->getlist().size() < 1)return masters;

	for (auto i : managers[id]->getlist())
	{
		masters.push_back(i);
	}
	return masters;
}