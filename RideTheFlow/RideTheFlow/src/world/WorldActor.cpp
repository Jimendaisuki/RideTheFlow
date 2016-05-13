#include "WorldActor.h"
#include<algorithm>
#include "../actor/ID.h"

WorldActor::WorldActor(){
	for (int i = ACTOR_ID::BEGIN_ACTOR; i <= ACTOR_ID::END_ACTOR; ++i)
		managers.emplace(ACTOR_ID(i), std::make_shared<ActorManager>());
	for (int i = EFFECT_ID::BEGIN_EFFECT; i <= EFFECT_ID::END_EFFECT; ++i)
		UImanagers.emplace(EFFECT_ID(i), std::make_shared<UIActorManager>());
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
void WorldActor::EffectAdd(EFFECT_ID id, UIActorPtr UIactor){
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
void WorldActor::EachUIActor(EFFECT_ID id, std::function<void(const UIActor&)> func)
{
	UImanagers[id]->EachActor(func);
}